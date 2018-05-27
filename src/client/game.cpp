#include "game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "../shared/logger.h"
#include "view/login-view.h"
#include "view/disconect-view.h"

Game::Game(Configuration* initial_configuration)
{

    this->initial_configuration = initial_configuration;
    this->correctly_initialized = false;

}

void Game::LogIn()
{
    InitSDL();


    LoginRequest* login_request = new LoginRequest();
    LoginView* login_view = new LoginView(this->renderer, SCREEN_HEIGHT, SCREEN_WIDTH, login_request);

    //Se abre la pantalla de login con su propio "game loop"
    login_view->Open(initial_configuration);

    this->client = new Client(initial_configuration);

    bool is_logged = false;
    std::string serialized_model;

    while (!is_logged && !login_view->IsUserQuit())
    {
        client->Init(login_request->GetServerIp());
        std::string login_response = client->LogIn(login_request);


        if ("login-fail" == login_response || "too-many-users" == login_response || "invalid-team" == login_response)
        {
            login_view->OpenErrorPage(initial_configuration, login_response);
        }
        else if("login-ok" == login_response)
        {
            is_logged = true;
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

        this->game_controller->Handle(keyboard_state_array);
        this->player_controller->Handle(keyboard_state_array);
        this->team_controller->Handle(keyboard_state_array);

        string serialized_match = this->client->GetGameState();
        if(serialized_match != "")
        {
            this->match->DeserializeAndUpdate(serialized_match);
        }

        RenderViews();

        //Manejo de frames por segundo: http://lazyfoo.net/SDL_tutorials/lesson16/index.php
        //SDL_Delay( ( 100 / FRAMES_PER_SECOND ));//TODO: configurar iteracion
        SDL_Delay(STOP_LOOP_MILLISECONDS);

        // Esto maneja el cierre del juego desde la cruz de la ventana
        while( SDL_PollEvent( &e ) != 0 )
        {
            //Apreta ESCAPE
            quit = ( e.type == SDL_QUIT );
        }
    }

}

void Game::End()
{
    Logger::getInstance()->info("==================JUEGO TERMINADO==================");

    DestroyModel();
    DestroyViews();
    DestroyControllers();
    SpritesProvider::FreeResources();
    SoundManager::FreeResources();
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
    Pitch* pitch = new Pitch();

    Formation* formation_team_a = new Formation(initial_configuration->GetFormation(), TEAM_NUMBER::TEAM_A);
    Team* team_a = new Team(formation_team_a, this->initial_configuration->GetTeamName(), this->initial_configuration->GetShirt(), TEAM_NUMBER::TEAM_A);

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++)
    {
        team_a->AddPlayer(new Player(i,TEAM_NUMBER::TEAM_A));
    }

    Formation* formation_team_b = new Formation(initial_configuration->GetFormation(), TEAM_NUMBER::TEAM_B);
    Team* team_b = new Team(formation_team_b, "team_b", "away", TEAM_NUMBER::TEAM_B); // TODO: TRAER NOMBRE DEL TEAM B Y CAMISETA DE CONFIG

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++)
    {
        team_b->AddPlayer(new Player(i, TEAM_NUMBER::TEAM_B));
    }

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

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++)
    {
        Player* player = match->GetTeamA()->GetPlayers()[i];
        PlayerView* player_view = new PlayerView(player);
        this->camera->Add(player_view);
    }

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++)
    {
        Player* player = match->GetTeamB()->GetPlayers()[i];
        PlayerView* player_view = new PlayerView(player);
        this->camera->Add(player_view);
    }

    BallView* ball_view = new BallView(match->GetBall());
    this->camera->Add(ball_view);
    this->camera->SetShowable(ball_view);
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
}

void Game::DestroyControllers()
{
    Logger::getInstance()->debug("DESTRUYENDO LOS CONTROLLERS");
    delete game_controller;
    delete player_controller;
    delete team_controller;
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

    SoundManager::LoadResources();

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
