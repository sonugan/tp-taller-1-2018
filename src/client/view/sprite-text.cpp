#include "sprite-text.h"
#include "../../shared/logger.h"

SpriteText::~SpriteText()
{
    Logger::getInstance()->debug("DESTRUYENDO SPRITETEXT" + this->path);
	this->Free();
}

bool SpriteText::LoadFromRenderedText( TTF_Font * font, std::string textureText, SDL_Color textColor, bool wrapped)
{	this->Free();

	SDL_Surface* textSurface = NULL;

	if (!wrapped)
    {
        // EL TEXTO QUEDA EN UNA SOLA LINEA
        textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
    }
    else
    {
        // PARA QUE EL TEXTO QUEDE EN MAS DE UNA LINEA
        textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, this->wrappedLength);
    }

	if( textSurface != NULL )
	{
	    this->texture = SDL_CreateTextureFromSurface( this->renderer, textSurface );
		if( this->texture == NULL )
		{
		    Logger::getInstance()->error(string ("SDL: No se pudo crear una textura desde un RendererText. SDL Error: ") + SDL_GetError());
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
        Logger::getInstance()->error(string("SDL_TTF: No se puede renderizar la TextSurface. SDL_TTF Error: ") + TTF_GetError());
	}

	if (this->texture == NULL)
    {
        Logger::getInstance()->error("SDL_TTF: No se pudo renderizar el texto '" + textureText + "'");
        return false;
	}

    return true;
}
