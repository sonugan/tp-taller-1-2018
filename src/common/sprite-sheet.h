#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SpriteSheet
{
	public:
		SpriteSheet(SDL_Renderer* renderer, std::string path);
		~SpriteSheet();
		void Free();
		void Render( int x, int y, SDL_Rect* clip, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	private:
		SDL_Texture* texture;
		SDL_Renderer* renderer;
		SDL_Surface* LoadSurface();
		bool LoadFromFile();
		int width;
		int height;
		std::string path;
};

#endif // SPRITESHEET_H
