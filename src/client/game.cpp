#include "game.h"
#include <iostream>
#include "../shared/logger.h"

Game::Game(Configuration* initial_configuration) {
    this->initial_configuration = initial_configuration;
    InitSDL();
    CreateModel();
    CreateViews();
    CreateControllers();
}

Game::~Game() {

}

void Game::RenderViews() {
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );

    this->camera->Render();
    SDL_RenderPresent( renderer );
}

void Game::Start() {
    Logger::getInstance()->info("==================COMIENZA EL JUEGO==================");
    this->quit = false;

    //Handler de eventos
    SDL_Event e;

    RenderViews();

    const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);

    // GAME LOOP
    while( !quit ) {
        this->game_controller->Handle(keyboard_state_array);
        this->player_controller->Handle(keyboard_state_array);
        this->team_controller->Handle(keyboard_state_array);

        RenderViews();

        //Manejo de frames por segundo: http://lazyfoo.net/SDL_tutorials/lesson16/index.php
        SDL_Delay( ( 1000 / FRAMES_PER_SECOND ));

        // Esto maneja el cierre del juego desde la cruz de la ventana
        while( SDL_PollEvent( &e ) != 0 ) {
            //Apreta ESCAPE
            quit = ( e.type == SDL_QUIT );
        }
    }

}

void Game::End() {
    Logger::getInstance()->info("==================JUEGO TERMINADO==================");

    DestroyModel();
    DestroyViews();
    DestroyControllers();
    SpritesProvider::FreeResources();
    SoundManager::FreeResources();
    CloseSDL();
}

void Game::CreateModel() {
    Logger::getInstance()->debug("CREANDO EL MODELO");
    Pitch* pitch = new Pitch();

    Formation* formation = new Formation(initial_configuration->GetFormation());
    Team* team_a = new Team(formation, this->initial_configuration->GetTeamName(), this->initial_configuration->GetShirt());

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        team_a->AddPlayer(new Player(i));
    }

    //selecciono por default al arquero
    team_a->GetPlayers()[0]->SetSelected(true);

    Ball* ball = new Ball();

    this->match = new Match(pitch, team_a, NULL, ball);
}

void Game::CreateViews() {

    Logger::getInstance()->debug("CREANDO LAS VISTAS");
    Location center(PITCH_WIDTH/2 - SCREEN_WIDTH/2, PITCH_HEIGHT/2 - SCREEN_HEIGHT/2, 0);
    this->camera = new Camera(PITCH_WIDTH, PITCH_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, this->renderer, &center);

    PitchView* pitch_view = new PitchView(this->match->GetPitch(), this->renderer);
    std::map <unsigned int, PlayerView*> player_views_map;
    this->camera->Add(pitch_view);

    BallView* ball_view = new BallView(match->GetBall(), this->renderer);
    this->camera->Add(ball_view);

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        Player* player = match->GetTeamA()->GetPlayers()[i];
        PlayerView* player_view = new PlayerView(player, this->renderer);
        player_views_map[i] = player_view;
        this->camera->Add(player_view);
        //selecciono por default al arquero
        if (i == 0) {
            this->camera->SetShowable(player_view);
        }
    }
    this->camera->SetPlayerViewsMap(player_views_map);
}

void Game::CreateControllers() {
    Logger::getInstance()->debug("CREANDO CONTROLLERS"); //  forward declaration
    team_controller = new TeamController(match->GetTeamA(), camera);
    player_controller = new PlayerController(match->GetTeamA());
    game_controller = new GameController(this);
}

void Game::DestroyModel() {
    Logger::getInstance()->debug("DESTRUYENDO EL MODELO");
    delete this->match;
}

void Game::DestroyViews() {
    Logger::getInstance()->debug("DESTRUYENDO LAS VISTAS");
    std::vector<AbstractView*> views = this->camera->GetViews();
    for (unsigned int i = 0; i < views.size(); i++) {
        delete (views[i]);
    }
    delete this->camera;
}

void Game::DestroyControllers() {
    Logger::getInstance()->debug("DESTRUYENDO LOS CONTROLLERS");
    delete game_controller;
    delete player_controller;
    delete team_controller;
}

void Game::InitSDL() {
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

    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        throw std::runtime_error(IMG_GetError());

    }
    SoundManager::LoadResources();

}

void Game::CloseSDL() {
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();

	Logger::getInstance()->debug("TERMINANDO PROGRAMA");
}

void Game::RequestQuit() {
    this->quit = true;
}
