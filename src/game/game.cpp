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
        }

        this->ChangeFormation(keyboard_state_array, &e);
        this->MoveUnselectedPlayersToDefaultPositions();
        this->ChangePlayerSelection(keyboard_state_array);
        //Si queda dentro del loop de eventos, se genera un delay
        this->MovePlayer(keyboard_state_array);
        RenderViews();

        //Manejo de frames por segundo: http://lazyfoo.net/SDL_tutorials/lesson16/index.php
        SDL_Delay( ( 1000 / FRAMES_PER_SECOND ));
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
    Formation* formation = new Formation(F_3_2_1);
    Team* team_a = new Team(formation);

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        team_a->AddPlayer(new Player(i));
    }

    //selecciono por default al arquero
    this->selected_player = team_a->GetPlayers()[0];
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
        //selecciono por default al arquero
        if (i == 0) {
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

bool Game::PlayerWithinMargins(Player* player) {
    //  64 es el tamaño del sprite del player... magic number.
    int half_player_sprite_size = 32;
    int x = player->GetLocation()->GetX() - camera->area->x;
    int y = player->GetLocation()->GetY() - camera->area->y;
    return x >= (Camera::CAMERA_MARGIN - half_player_sprite_size) && y >= (Camera::CAMERA_MARGIN - half_player_sprite_size) && x <= (SCREEN_WIDTH - Camera::CAMERA_MARGIN + half_player_sprite_size) && y <= (SCREEN_HEIGHT - Camera::CAMERA_MARGIN + half_player_sprite_size);
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
            if (!possible_player->IsSelected() && PlayerWithinMargins(possible_player)) {
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
            camera->SetLocatable(player_views_map[selected_player->GetPositionIndex()]);
        }
    }
}

void Game::ChangeFormation(const Uint8 *keyboard_state_array, SDL_Event* e) {
    if(FKeySelected(keyboard_state_array, e)) {
        FORMATION old_formation_value = match->GetTeamA()->GetFormation()->GetValue();
        if (old_formation_value == F_3_3) {
            match->GetTeamA()->SetFormation(new Formation(F_3_2_1));
        } else if (old_formation_value == F_3_2_1) {
            match->GetTeamA()->SetFormation(new Formation(F_3_1_2));
        } else if (old_formation_value == F_3_1_2) {
            match->GetTeamA()->SetFormation(new Formation(F_3_3));
        }
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

bool Game::FKeySelected(const Uint8 *keyboard_state_array, SDL_Event* e)
{
    return keyboard_state_array[SDL_SCANCODE_F];
}
