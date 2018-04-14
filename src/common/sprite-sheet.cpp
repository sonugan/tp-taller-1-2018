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

	SDL_Surface* loadedSurface = IMG_Load( this->path.c_str() );
	if( loadedSurface == NULL )
	{
		Logger::getInstance()->error("No se puede crear el SpriteSheet ya que no se encontro la imagen '" + this->path + "'.");
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( this->renderer, loadedSurface );
		if( newTexture == NULL )
		{
			Logger::getInstance()->debug("No se puede crear una textura desde '" + this->path + "'. Error de SDL: " + SDL_GetError());
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

void SpriteSheet::SetColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( texture, red, green, blue );
}

void SpriteSheet::SetBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( texture, blending );
}

void SpriteSheet::SetAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( texture, alpha );
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

int SpriteSheet::GetWidth()
{
	return width;
}

int SpriteSheet::GetHeight()
{
	return height;
}
