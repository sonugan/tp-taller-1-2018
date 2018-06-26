#include "game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "../shared/logger.h"
#include "view/login-view.h"
#include "view/disconect-view.h"

Game::Game(Configuration* initial_configuration) // @suppress("Class members should be properly initialized")
{
    this->initial_configuration = initial_configuration;
    this->correctly_initialized = false;
}

void Game::LogIn()
{
    InitSDL();

    LoginRequest* login_request = new LoginRequest();
    LoginView* login_view = new LoginView(this->renderer, SCREEN_HEIGHT, SCREEN_WIDTH, login_request);

    CreateGameMusic();

    this->game_music->PlayLoginTheme();

    //Se abre la pantalla de login con su propio "game loop"
    login_view->Open(initial_configuration);

    this->client = new Client(initial_configuration);


    bool is_logged = false;
    std::string serialized_model;

    while (!is_logged && !login_view->IsUserQuit())
    {
        client->Init();
        std::string login_response = client->LogIn(login_request);

        if ("login-fail" == login_response || "too-many-users" == login_response || "invalid-team" == login_response || login_response == "non-existent-user")
        {
            login_view->OpenErrorPage(initial_configuration, login_response);
        }
        else if("login-ok" == login_response || "choose-formation" == login_response)
        {
            is_logged = true;
            if ("choose-formation" == login_response) {
                //Si recibo mensaje de elegir formacion muestro pantalla
                ChangeFormationRequest* cfRequest = new ChangeFormationRequest();
                bool x_pressed = login_view->OpenFormationPage(cfRequest);
                if (x_pressed || !this->client->ChangeFormation(cfRequest)) {
                    //El cliente cerro el programa o no se pudo cambiar la formacion por error en socket -> disconnect
                    QuitRequest* quit_request = new QuitRequest(this->user->GetUsername());
                    this->client->Quit(quit_request);

                    /** ESTO TIRA bad_alloc */
                }
            }

            login_view->OpenWaitingPage();
            while (serialized_model.empty())
            {
                serialized_model = client->WaitForGameStart();
            }
            //TODO sacar esto y ver que se rompe

            this->user = new User(login_request->GetUsername(), login_request->GetPassword(), login_view->GetTeamNumber(), USER_COLOR::RED);

            CreateModel(serialized_model);
            CreateViews();
            CreateControllers();

            this->correctly_initialized = true;
        }
    }

    //Libero recursos de la vista

    login_view->Free();
    delete login_view;
    delete login_request;
}

Game::~Game()
{
}

bool Game::IsCorrectlyInitialized()
{
    return this->correctly_initialized;
}

void Game::RenderViews()
{
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );

    this->camera->Render();

    this->score_view->Render(this->match->GetTeamA(), this->match->GetTeamB());
    this->timer_view->Render(this->match->GetRemainingTime());
    this->match_time_view->Render(this->match->GetMatchTime());

    if (this->match->GetMatchState()->IsFinished())
    {
        this->game_statistics_view->Render(this->match->GetTeamA(), this->match->GetTeamB(), this->match->GetScoreBoard());
    }

    SDL_RenderPresent( renderer );
}

void Game::Start()
{
    Logger::getInstance()->info("==================COMIENZA EL JUEGO==================");

    this->quit = false;

    //Handler de eventos
    SDL_Event e;

    RenderViews();

    const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);

    MATCH_STATE_TYPE last_match_state = (MATCH_STATE_TYPE)-1;

    this->game_music->PlayMainTheme();
    this->sound_manager->PlayKickOffSound();

    // GAME LOOP
    while( !quit )
    {
        if (!this->client->IsConnected())
        {
            Logger::getInstance()->debug("(Game:Start) Desconectado.");
            DisconetView* disconect_view = new DisconetView(this->renderer, SCREEN_HEIGHT, SCREEN_WIDTH);
            disconect_view->OpenConectionErrorPage();
            if(disconect_view->ExitGame())
            {
                quit = true;
            }
            else if(disconect_view->Reconnect())
            {
                //TODO: reconexion
                disconect_view->OpenConectingPage();
            }
            delete disconect_view;
            continue;
        }

        if (this->match->GetMatchState()->IsPlaying())
        {
			this->team_controller->Handle(keyboard_state_array);
			this->player_controller->SetEvent(e);
			this->player_controller->Handle(keyboard_state_array);
        }

        this->game_controller->Handle(keyboard_state_array);
        this->music_controller->Handle(keyboard_state_array);

        string serialized_match = this->client->GetGameState();
        if(serialized_match != "")
        {
            this->match->DeserializeAndUpdate(serialized_match);
            Logger::getInstance()->debug("(GameLoop) Formacion team a: " + to_string(this->match->GetTeamA()->GetFormation()->GetValue()));
            Logger::getInstance()->debug("(GameLoop) Formacion team b: " + to_string(this->match->GetTeamB()->GetFormation()->GetValue()));
        }

        RenderViews();

        if (MatchStateHasChanged(last_match_state)) {
            // Chequeo si el match state cambio, ya que sino el mismo sonido se
            // repetia mas de una vez, por ser muy rapido el game loop
            PlaySounds();
        }

        //Manejo de frames por segundo: http://lazyfoo.net/SDL_tutorials/lesson16/index.php
        //SDL_Delay( ( 100 / FRAMES_PER_SECOND ));//TODO: configurar iteracion
        SDL_Delay(STOP_LOOP_MILLISECONDS);

        // Esto maneja el cierre del juego desde la cruz de la ventana
        while( SDL_PollEvent( &e ) != 0 )
        {
            //Apreta ESCAPE
            quit = ( e.type == SDL_QUIT );
        }

        last_match_state = this->match->GetMatchState()->GetType();
    }

}

void Game::End()
{
    Logger::getInstance()->info("==================JUEGO TERMINADO==================");

    DestroyModel();
    DestroyViews();
    DestroyControllers();
    DestroyGameMusic();
    SpritesProvider::FreeResources();
    //SoundManager::FreeResources();
    CloseSDL();
}

void Game::CreateModel(std::string serialized_model)
{
    Logger::getInstance()->debug("CREANDO EL MODELO");

    /*
    ACA ESTAMOS INSTANCIANDO EL MODELO COMO CUANDO NO HABÍA SERVER
    Y LUEGO LO ACTUALIZAMOS CON LO QUE MANDA EL SERVER.
    POR QUE? PORQUE NO QUEREMOS ROMPER COSAS QUE ANTES FUNCIONABAN.
     */

    Formation* formation_team_a = new Formation(initial_configuration->GetFormation(), TEAM_NUMBER::TEAM_A);
    Team* team_a = new Team(formation_team_a, this->initial_configuration->GetTeamName(), this->initial_configuration->GetShirt(), TEAM_NUMBER::TEAM_A);

    Keeper* keeper_a = new Keeper();
	Player* new_player_a;
	for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++)
	{
		new_player_a = new Player(i, team_a);
		// Se setea de forma arbitratia que el team A sea el primero en sacar
		new_player_a->SetInitialLocation(formation_team_a->GetKickoffLocationForPlayer(i, true));
		team_a->AddPlayer(new_player_a);
	}
    team_a->SetKeeper(keeper_a);

    Formation* formation_team_b = new Formation(initial_configuration->GetFormation(), TEAM_NUMBER::TEAM_B);
    Team* team_b = new Team(formation_team_b, "team_b", "away", TEAM_NUMBER::TEAM_B); // TODO: TRAER NOMBRE DEL TEAM B Y CAMISETA DE CONFIG

    Keeper* keeper_b = new Keeper();
	Player* new_player_b;
	for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++)
	{
		new_player_b = new Player(i, team_b);
		new_player_b->SetInitialLocation(formation_team_b->GetKickoffLocationForPlayer(i, false));
		team_b->AddPlayer(new_player_b);
	}
    team_b->SetKeeper(keeper_b);

    // DEFINIR COMO SE SELECCIONA EL JUGADOR
    if (user->GetSelectedTeam() == TEAM_NUMBER::TEAM_A)
    {
        team_a->GetPlayers()[5]->SetPlayerColor(this->user->GetUserColor());
    }
    else
    {
        team_b->GetPlayers()[5]->SetPlayerColor(this->user->GetUserColor());
    }

    Ball* ball = new Ball();

    Pitch* pitch = new Pitch(team_a, team_b);
    this->match = new Match(pitch, team_a, team_b, ball);

    this->match->DeserializeAndUpdate(serialized_model);

    this->client->SetMatch(this->match);
}

void Game::CreateViews()
{

    Logger::getInstance()->debug("CREANDO LAS VISTAS");
    Location center(PITCH_WIDTH/2 - SCREEN_WIDTH/2, PITCH_HEIGHT/2 - SCREEN_HEIGHT/2, 0);
    this->camera = new Camera(PITCH_WIDTH, PITCH_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, this->renderer, &center);

    PitchView* pitch_view = new PitchView(this->match->GetPitch());
    this->camera->Add(pitch_view);

    Keeper* keeper_a = match->GetTeamA()->GetKeeper();
    KeeperView* keeper_a_view = new KeeperView(keeper_a);
    this->camera->Add(keeper_a_view);
    MiniPlayerView* mini_keeper_a_view = new MiniPlayerView(keeper_a->GetLocation(), keeper_a->PlaysForTeamA(), PITCH_HEIGHT, PITCH_WIDTH);
    this->camera->AddMiniPlayerView(mini_keeper_a_view);
    for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++)
    {
        Player* player = match->GetTeamA()->GetPlayerByPositionIndex(i);

        PlayerView* player_view = new PlayerView(player);
        this->camera->Add(player_view);

        MiniPlayerView* mini_player_view = new MiniPlayerView(player->GetLocation(), player->PlaysForTeamA(), PITCH_HEIGHT, PITCH_WIDTH);
        this->camera->AddMiniPlayerView(mini_player_view);
    }

    Keeper* keeper_b = match->GetTeamB()->GetKeeper();
    KeeperView* keeper_b_view = new KeeperView(keeper_b);
    this->camera->Add(keeper_b_view);
    MiniPlayerView* mini_keeper_b_view = new MiniPlayerView(keeper_b->GetLocation(), keeper_b->PlaysForTeamA(), PITCH_HEIGHT, PITCH_WIDTH);
    this->camera->AddMiniPlayerView(mini_keeper_b_view);
    for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++)
    {
        Player* player = match->GetTeamB()->GetPlayerByPositionIndex(i);

        PlayerView* player_view = new PlayerView(player);
        this->camera->Add(player_view);

        MiniPlayerView* mini_player_view = new MiniPlayerView(player->GetLocation(), player->PlaysForTeamA(), PITCH_HEIGHT, PITCH_WIDTH);
        this->camera->AddMiniPlayerView(mini_player_view);
    }

    BallView* ball_view = new BallView(match->GetBall());
    this->camera->Add(ball_view);
    this->camera->SetShowable(ball_view);

    MiniBallView* mini_ball_view = new MiniBallView(match->GetBall(), PITCH_HEIGHT, PITCH_WIDTH);
    this->camera->AddMiniBallView(mini_ball_view);

    SplashView* splash_view = new SplashView(match->GetMatchState());
    this->camera->Add(splash_view);

    this->timer_view = new TimerView(renderer);
    this->score_view = new ScoreView(renderer);
    this->match_time_view = new MatchTimeView(renderer);
    this->game_statistics_view = new GameStatisticsView(renderer);

}

void Game::CreateControllers()
{
    Logger::getInstance()->debug("CREANDO CONTROLLERS"); //  forward declaration

    //OBTENER EL EQUIPO DEL USER PARA CREAR LOS CONTROLADORES

    if (this->user->GetSelectedTeam() == TEAM_NUMBER::TEAM_A)
    {
        team_controller = new TeamController(match->GetTeamA(), this->client, camera);
        player_controller = new PlayerController(match->GetTeamA(), this->client);
    }
    else
    {
        team_controller = new TeamController(match->GetTeamB(), this->client, camera);
        player_controller = new PlayerController(match->GetTeamB(), this->client);
    }

    game_controller = new GameController(this, this->client);
    music_controller = new GameMusicController(this->game_music);
}

void Game::DestroyModel()
{
    Logger::getInstance()->debug("DESTRUYENDO EL MODELO");
    delete this->match;
}

void Game::DestroyViews()
{
    Logger::getInstance()->debug("DESTRUYENDO LAS VISTAS");

    std::vector<AbstractView*> views = this->camera->GetViews();
    for (unsigned int i = 0; i < views.size(); i++)
    {
        delete (views[i]);
    }

    delete this->camera;
    delete this->timer_view;
    delete this->score_view;
    delete this->match_time_view;
    delete this->game_statistics_view;
}

void Game::DestroyControllers()
{
    Logger::getInstance()->debug("DESTRUYENDO LOS CONTROLLERS");
    delete game_controller;
    delete player_controller;
    delete team_controller;
    delete music_controller;
}

void Game::InitSDL()
{
    Logger::getInstance()->debug("INICIALIZANDO SDL");
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        throw std::runtime_error(SDL_GetError());
    }

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        Logger::getInstance()->debug( "WARNING (SDL): Linear texture filtering not enabled!" );
    }

    window = SDL_CreateWindow( "Tehkan world cup", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        throw std::runtime_error(SDL_GetError());
    }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL )
    {
        throw std::runtime_error(SDL_GetError());
    }
    SpritesProvider::SetRenderer(renderer);

    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        throw std::runtime_error(IMG_GetError());
    }

    //SoundManager::LoadResources();

    if( TTF_Init() == -1 )
    {
        throw std::runtime_error(TTF_GetError());
    }

}

void Game::CloseSDL()
{
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    Logger::getInstance()->debug("TERMINANDO PROGRAMA");
}

void Game::Quit()
{
    this->quit = true;
}

User* Game::GetUser()
{
    return user;
}

bool Game::MatchStateHasChanged(int last_match_state)
{
    return last_match_state != -1 && last_match_state != this->match->GetMatchState()->GetType();
}

void Game::CreateGameMusic()
{
    this->game_music = new GameMusic();
    this->sound_manager = new SoundManager();
}

void Game::DestroyGameMusic()
{
    delete this->game_music;
    delete this->sound_manager;
}

void Game::PlaySounds()
{
    if (this->match->GetMatchState()->IsKickOff())
    {
        this->sound_manager->PlayKickOffSound();
    }
    else if (this->match->GetMatchState()->IsTimeup())
    {
        this->sound_manager->PlayTimeUpSound();
    }
    else if (this->match->GetMatchState()->IsGoal())
    {
        PlayGoalSound();
    }

}

void Game::PlayGoalSound()
{
    if (this->game_music->IsPlaying())
    {
        // Si estaba sonando el tema principal, tengo que pausarlo y despues
        // reaundarlo, ya que sino pisa la musica de gol
        this->game_music->Pause();
        this->sound_manager->PlayGoalSound();
        this->game_music->Resume();
    }
    else
    {
        this->sound_manager->PlayGoalSound();
    }
}



