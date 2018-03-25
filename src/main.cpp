/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include<iostream>
#include "common/sprite-sheet.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Walking animation
const int FRAME_RETARDANT = 4;
const int WALKING_ANIMATION_FRAMES = 4;
SpriteSheet* gSpriteSheetTexture;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool createSpriteSheet()
{
	//Loading success flag
	bool success = true;

        SDL_Rect* sprite1 = new SDL_Rect();
		sprite1->x =   0;
		sprite1->y =   0;
		sprite1->w =  64;
		sprite1->h = 205;

		SDL_Rect* sprite2 = new SDL_Rect();
		sprite2->x =  64;
		sprite2->y =   0;
		sprite2->w =  64;
		sprite2->h = 205;

		SDL_Rect* sprite3 = new SDL_Rect();
		sprite3->x = 128;
		sprite3->y =   0;
		sprite3->w =  64;
		sprite3->h = 205;


		SDL_Rect* sprite4 = new SDL_Rect();
		sprite4->x = 196;
		sprite4->y =   0;
		sprite4->w =  64;
		sprite4->h = 205;

		std::vector<SDL_Rect*> clips;
        clips.push_back(sprite1);
        clips.push_back(sprite2);
        clips.push_back(sprite3);
        clips.push_back(sprite4);

	gSpriteSheetTexture = new SpriteSheet(gRenderer, "foo.png", clips);

	return success;
}

void close()
{

	//Free loaded images
	gSpriteSheetTexture->Free();
	delete gSpriteSheetTexture;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void clearScreen() {
    //Clear screen
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );
}

int main( int argc, char* args[] )
{
    std::cout << "hello!";
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !createSpriteSheet() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Current animation frame
			int frame = 0;
			int x = 0;
			int y = 0;

			clearScreen();
			SDL_RenderPresent( gRenderer );

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
					} else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
{                       ++frame;
					    std::cout << "Frame: " << frame << "\n";
                        if( (frame / FRAME_RETARDANT) >= WALKING_ANIMATION_FRAMES )
                        {
                            frame = 0;
                        }

                        if (keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_DOWN]))
                        {
                            --y;
                        }
                        else if (!keyboard_state_array[SDL_SCANCODE_UP] && keyboard_state_array[SDL_SCANCODE_DOWN])
                        {
                            ++y;
                        }

                        if (keyboard_state_array[SDL_SCANCODE_RIGHT] && !keyboard_state_array[SDL_SCANCODE_LEFT])
                        {
                            ++x;
                        }
                        else if (!keyboard_state_array[SDL_SCANCODE_RIGHT] && keyboard_state_array[SDL_SCANCODE_LEFT])
                        {
                            --x;
                        }

                        clearScreen();

                        SDL_Rect* currentClip = gSpriteSheetTexture->GetClips()[ frame / FRAME_RETARDANT];
                        gSpriteSheetTexture->Render( x, y, currentClip );

                        //Update screen
                        SDL_RenderPresent( gRenderer );
                    }

				}

                if (x > SCREEN_WIDTH) {
                    x = 0;
                }
                if (y > SCREEN_HEIGHT) {
                    y = 0;
                }
                if (x < 0) {
                    x = SCREEN_WIDTH;
                }
                if (y < 0) {
                    y = SCREEN_HEIGHT;
                }

			}
		}
	}

	//Free resources and close SDL
	close();

	std::cout << "bye.";

	return 0;
}
