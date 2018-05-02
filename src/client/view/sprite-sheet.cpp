#include "sprite-sheet.h"
#include "../../shared/logger.h"


SpriteSheet::SpriteSheet(SDL_Renderer* renderer, std::string path, bool isImage)
{
    Logger::getInstance()->debug("CREANDO SPRITESHEET");
	this->renderer = renderer;
	// TODO: deberia levantarse desde config.
	this->path = "src/client/sprites/" + path;
	this->texture = NULL;
	this->width = 0;
	this->height = 0;
	if (isImage) {
        LoadFromFile();
	}
}

SpriteSheet::~SpriteSheet()
{
    Logger::getInstance()->debug("DESTRUYENDO SPRITESHEET");
	Free();
}

bool SpriteSheet::LoadFromFile()
{
	this->Free();
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
	if( this->texture != NULL )
	{
		SDL_DestroyTexture( this->texture );
		this->texture = NULL;
		this->width = 0;
		this->height = 0;
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
        surfaceLoad = IMG_Load( "src/client/sprites/error.png" );
    }
    return surfaceLoad;
}

void SpriteSheet::Render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, this->width, this->height };
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx( this->renderer, texture, clip, &renderQuad, angle, center, flip);
}

bool SpriteSheet::LoadFromRenderedText( TTF_Font * font, std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	this->Free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        this->texture = SDL_CreateTextureFromSurface( this->renderer, textSurface );
		if( this->texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			this->width = textSurface->w;
			this->height = textSurface->h;
		}

		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return this->texture != NULL;
}

int SpriteSheet::GetWidth()
{
    return this->width;
}

int SpriteSheet::GetHeight()
{
    return this->height;
}
