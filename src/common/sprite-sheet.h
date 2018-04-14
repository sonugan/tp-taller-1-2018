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
		SpriteSheet(SDL_Renderer* renderer, std::string path);

		~SpriteSheet();

		void Free();

		void SetColor( Uint8 red, Uint8 green, Uint8 blue );

		void SetBlendMode( SDL_BlendMode blending );

		void SetAlpha( Uint8 alpha );

		void Render( int x, int y, SDL_Rect* clip, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		int GetWidth();
		int GetHeight();

	private:
		SDL_Texture* texture;

		SDL_Renderer* renderer;

		bool LoadFromFile();
		int width;
		int height;
		std::string path;
};

#endif // SPRITESHEET_H
