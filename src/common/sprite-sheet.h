#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SpriteSheet
{
	public:
		//Initializes variables
		SpriteSheet(SDL_Renderer* gRenderer, std::string path, std::vector<SDL_Rect*> clips);

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
		void Render( int x, int y, SDL_Rect* clip = NULL );

		//Gets image dimensions
		int GetWidth();
		int GetHeight();

		std::vector<SDL_Rect*> GetClips();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		SDL_Renderer* gRenderer;

		std::vector<SDL_Rect*> clips;

        //Loads image at specified path
		bool LoadFromFile();
		//Image dimensions
		int mWidth;
		int mHeight;
		std::string path;
};

#endif // SPRITESHEET_H
