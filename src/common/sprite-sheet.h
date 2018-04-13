#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SpriteSheet
{
	public:
		//Initializes variables
		SpriteSheet(SDL_Renderer* renderer, std::string path);

		//Deallocates memory
		~SpriteSheet();

		//Deallocates texture
		void Free();

		//Set color modulation
		void SetColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void SetBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void SetAlpha( Uint8 alpha );

		//Renders texture at given point
		void Render( int x, int y, SDL_Rect* clip, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int GetWidth();
		int GetHeight();

	private:
		//The actual hardware texture
		SDL_Texture* texture;

		SDL_Renderer* renderer;

		//Loads surface at specified path
		SDL_Surface* LoadSurface();

        //Loads image at specified path
		bool LoadFromFile();
		//Image dimensions
		int width;
		int height;
		std::string path;
};

#endif // SPRITESHEET_H
