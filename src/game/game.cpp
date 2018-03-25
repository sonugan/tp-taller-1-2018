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
    for (unsigned int i = 0; i < views.size(); i++) {
        views[i]->Render();
    }
    SDL_RenderPresent( renderer );
}

void Game::Start()
{
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

            if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){

                if (keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_DOWN])) {
                    player->MoveUp(1);
                } else if (!keyboard_state_array[SDL_SCANCODE_UP] && keyboard_state_array[SDL_SCANCODE_DOWN]) {
                    player->MoveDown(1);
                }

                if (keyboard_state_array[SDL_SCANCODE_RIGHT] && !keyboard_state_array[SDL_SCANCODE_LEFT]) {
                    player->MoveRight(1);
                } else if (!keyboard_state_array[SDL_SCANCODE_RIGHT] && keyboard_state_array[SDL_SCANCODE_LEFT]) {
                    player->MoveLeft(1);
                }

                RenderViews();
            }
        }
    }

}

void Game::End()
{
    std::cout << "Game::End" << "\n";
    DestroyModel();
    DestroyViews();
    CloseSDL();
}

void Game::CreateModel() {
    std::cout << "Game::CreateModel" << "\n";
    this->pitch = new Pitch();
    this->player = new Player();
}

void Game::CreateViews() {
    std::cout << "Game::CreateViews" << "\n";
    PitchView* pitch_view = new PitchView(this->pitch, this->renderer);
    PlayerView* player_view = new PlayerView(this->player, this->renderer);
    this->views.push_back(pitch_view);
    this->views.push_back(player_view);
}

void Game::DestroyModel() {
    std::cout << "Game::DestroyModel" << "\n";
    delete this->pitch;
    delete this->player;
}

void Game::DestroyViews() {
    std::cout << "Game::DestroyViews()" << "\n";
    for (unsigned int i = 0; i < views.size(); i++) {
        delete (views[i]);
    }
}

void Game::InitSDL()
{
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
