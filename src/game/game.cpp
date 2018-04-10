#include "game.h"
#include <iostream>

Game::Game() {
    InitSDL();
    CreateModel();
    CreateViews();
}

Game::~Game() {
    std::cout << "Destructor de Game" << "\n";
    DestroyModel();
    DestroyViews();
}

void Game::RenderViews() {
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );

    this->camera->Render();
    SDL_RenderPresent( renderer );
}

void Game::Start() {
    std::cout << "Game::Start" << "\n";

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    RenderViews();

    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

            //this->MovePlayer(&e, keyboard_state_array);
        }

        this->MoveUnselectedPlayersToDefaultPositions();
        this->ChangePlayerSelection(keyboard_state_array);
        //Si queda dentro del loop de eventos, se genera un delay
        this->PlayerPlay(keyboard_state_array);

        RenderViews();

        //Manejo de frames por segundo: http://lazyfoo.net/SDL_tutorials/lesson16/index.php
        SDL_Delay( ( 1000 / FRAMES_PER_SECOND ));
    }

}

void Game::PlayerPlay(const Uint8 *keyboard_state_array) {

    bool playerKicked = this->KickPlayer(keyboard_state_array);

    if (!playerKicked) {
        bool playerRecovered = this->PlayerRecoverBall(keyboard_state_array);
        if (!playerRecovered) {
            this->MovePlayer(keyboard_state_array);
        }
    }

}

void Game::End() {
    std::cout << "Game::End" << "\n";
    DestroyModel();
    DestroyViews();
    CloseSDL();
}

void Game::CreateModel() {
    std::cout << "Game::CreateModel" << "\n";
    Pitch* pitch = new Pitch();
    Formation* formation = new Formation(F_3_3);
    Team* team_a = new Team(formation);

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        team_a->AddPlayer(new Player(i));
    }

    //selecciono por default al delantero del medio
    this->selected_player = team_a->GetPlayers()[5];
    this->selected_player->SetSelected(true);

    this->match = new Match(pitch, team_a, NULL);
}

void Game::CreateViews() {
    std::cout << "Game::CreateViews" << "\n";
    Location center(PITCH_WIDTH/2 - SCREEN_WIDTH/2, PITCH_HEIGHT/2 - SCREEN_HEIGHT/2, 0);
    this->camera = new Camera(PITCH_WIDTH, PITCH_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, this->renderer, &center);

    PitchView* pitch_view = new PitchView(this->match->GetPitch(), this->renderer);
    this->camera->Add(pitch_view);
    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        Player* player = match->GetTeamA()->GetPlayers()[i];
        PlayerView* player_view = new PlayerView(player, this->renderer);
        player_views_map[i] = player_view;
        this->camera->Add(player_view);
        //selecciono por default al delantero del medio
        if (i == 5) {
            this->camera->SetLocatable(player_view);
        }
    }

}

void Game::DestroyModel() {
    std::cout << "Game::DestroyModel" << "\n";
    delete this->match;
}

void Game::DestroyViews() {
    std::cout << "Game::DestroyViews()" << "\n";
    std::vector<AbstractView*> views = this->camera->GetViews();
    for (unsigned int i = 0; i < views.size(); i++) {
        delete (views[i]);
    }
    delete this->camera;
}

void Game::InitSDL() {
    std::cout << "Game::InitSDL" << "\n";
    //Starts up SDL and creates window
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	    throw std::runtime_error(SDL_GetError());
	}
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }
    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        throw std::runtime_error(SDL_GetError());
    }

    //Create vsynced renderer for window
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL )
    {
        throw std::runtime_error(SDL_GetError());
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        throw std::runtime_error(IMG_GetError());

    }

}

void Game::CloseSDL()
{
	//Destroy window
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	std::cout << "bye." << "\n";
}

Player* Game::FindNextPlayerToSelect() {
    Player* next_player = NULL;
    unsigned int new_selected_player_position_index = selected_player->GetPositionIndex();
    for (unsigned int i = 0; i < (Team::TEAM_SIZE - 1); i++) {

            if (new_selected_player_position_index == Team::TEAM_SIZE-1) {
                new_selected_player_position_index = 0;
            } else {
                new_selected_player_position_index++;
            }
            // El próximo jugador tiene que estar dentro de la cámara y no tiene que estar seleccionado
            Player* possible_player = match->GetTeamA()->GetPlayers()[new_selected_player_position_index];
            if (!possible_player->IsSelected()
                && ((possible_player->GetLocation()->GetX() - camera->area->x) >= 0)
                && ((possible_player->GetLocation()->GetY() - camera->area->y) >= 0)) {
                    next_player = possible_player;
                    break;
                }
    }
    return next_player;
}

void Game::ChangePlayerSelection(const Uint8 *keyboard_state_array) {
    if(CKeySelected(keyboard_state_array)) {

        Player* next_player = FindNextPlayerToSelect();
        if (next_player != NULL) {
            selected_player->SetSelected(false);
            selected_player = next_player;
            selected_player->SetSelected(true);
//            camera->SetLocatable(player_views_map[selected_player->GetPositionIndex()]);
        }

//        selected_player->SetSelected(false);
//        unsigned int new_selected_player_position_index = selected_player->GetPositionIndex() + 1;
//        if (new_selected_player_position_index >= Team::TEAM_SIZE) {
//            new_selected_player_position_index = 0;
//        }
//        selected_player = match->GetTeamA()->GetPlayers()[new_selected_player_position_index];
//        selected_player->SetSelected(true);
//        camera->SetLocatable(player_views_map[selected_player->GetPositionIndex()]);
    }
}

void Game::MovePlayer(const Uint8 *keyboard_state_array)
{
    if (UpKeySelected(keyboard_state_array) && RightKeySelected(keyboard_state_array)) {
        selected_player->MoveUpToRight();
    } else if (UpKeySelected(keyboard_state_array) && LeftKeySelected(keyboard_state_array)) {
        selected_player->MoveUpToLeft();
    } else if (DownKeySelected(keyboard_state_array) && RightKeySelected(keyboard_state_array)) {
        selected_player->MoveDownToRight();
    } else if (DownKeySelected(keyboard_state_array) && LeftKeySelected(keyboard_state_array)) {
        selected_player->MoveDownToLeft();
    } else if (UpKeySelected(keyboard_state_array)) {
        selected_player->MoveUp();
    } else if(RightKeySelected(keyboard_state_array)) {
        selected_player->MoveRight();
    } else if(LeftKeySelected(keyboard_state_array)) {
        selected_player->MoveLeft();
    } else if(DownKeySelected(keyboard_state_array)) {
        selected_player->MoveDown();
    }
}

void Game::MoveUnselectedPlayersToDefaultPositions() {
    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        Player* player = match->GetTeamA()->GetPlayers()[i];
        if (!player->IsSelected()) {
            player->GoBackToDefaultPosition();
        }
    }
}

bool Game::KickPlayer(const Uint8 *keyboard_state_array)
{
    if (SpaceBarSelected(keyboard_state_array)) {
        selected_player->Kick();
        return true;
    }
    return false;
}

bool Game::PlayerRecoverBall(const Uint8 *keyboard_state_array)
{
    if (keyboard_state_array[SDL_SCANCODE_V]) {
        selected_player->RecoverBall();
        return true;
    }
    return false;
}

bool Game::CKeySelected(const Uint8 *keyboard_state_array)
{
    return keyboard_state_array[SDL_SCANCODE_C];
}

bool Game::UpKeySelected(const Uint8 *keyboard_state_array)
{
    return keyboard_state_array[SDL_SCANCODE_UP] || keyboard_state_array[SDL_SCANCODE_W];
}

bool Game::RightKeySelected(const Uint8 *keyboard_state_array)
{
    return keyboard_state_array[SDL_SCANCODE_RIGHT] || keyboard_state_array[SDL_SCANCODE_D];
}

bool Game::LeftKeySelected(const Uint8 *keyboard_state_array)
{
    return keyboard_state_array[SDL_SCANCODE_LEFT] || keyboard_state_array[SDL_SCANCODE_A];
}

bool Game::DownKeySelected(const Uint8 *keyboard_state_array)
{
    return keyboard_state_array[SDL_SCANCODE_DOWN] || keyboard_state_array[SDL_SCANCODE_S];
}

bool Game::SpaceBarSelected(const Uint8 *keyboard_state_array)
{
    return keyboard_state_array[SDL_SCANCODE_SPACE];
}

