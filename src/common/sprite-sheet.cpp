#include "sprite-sheet.h"
#include "logger.h"


SpriteSheet::SpriteSheet(SDL_Renderer* renderer, std::string path)
{
	this->renderer = renderer;
	this->path = "src/sprites/" + path;
	texture = NULL;
	width = 0;
	height = 0;
	LoadFromFile();
}

SpriteSheet::~SpriteSheet()
{
    Logger::getInstance()->debug("DESTRUYENDO SPRITESHEET");
	Free();
}

bool SpriteSheet::LoadFromFile()
{
	Free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = LoadSurface();
	if( loadedSurface == NULL )
	{
		stringstream ss;
		ss << "No se puede cargar la imagen src/sprites/error.png. Error: " << IMG_GetError();
		Logger::getInstance()->error(ss.str());
	}
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( this->renderer, loadedSurface );
        if( newTexture == NULL )
        {
			stringstream ss;
			ss << "No se puede crear la textura desde " << this->path.c_str() << ". Error: " << IMG_GetError();
			Logger::getInstance()->error(ss.str());
        }
        else
        {
            this->width = loadedSurface->w;
            this->height = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }

	this->texture = newTexture;
	return this->texture != NULL;
}

void SpriteSheet::Free()
{
	if( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
		width = 0;
		height = 0;
	}
}

SDL_Surface* SpriteSheet::LoadSurface()
{
    SDL_Surface* surfaceLoad = IMG_Load( this->path.c_str() );
    if (surfaceLoad == NULL)
    {
		stringstream ss;
		ss << "No se puede cargar la imagen " << this->path.c_str() << ". Error: " << IMG_GetError();
		Logger::getInstance()->error(ss.str());
        surfaceLoad = IMG_Load( "src/sprites/error.png" );
    }
    return surfaceLoad;
}

void SpriteSheet::Render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, width, height };
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip);
}
