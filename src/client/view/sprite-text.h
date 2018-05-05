#ifndef SPRITETEXT_H
#define SPRITETEXT_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sprite-sheet.h"
#include "../../shared/logger.h"

class SpriteText : public SpriteSheet
{
	public:
		SpriteText(SDL_Renderer* renderer, TTF_Font* fontStyle, std::string text, SDL_Color color) : SpriteSheet (renderer, "")
		{
            Logger::getInstance()->debug("CREANDO SPRITETEXT para '" + text + "'");
            this->renderer = renderer;
            // TODO: deberia levantarse desde config.
            this->path = "src/client/sprites/" + text;
            this->texture = NULL;
            this->width = 0;
            this->height = 0;
            this->LoadFromRenderedText(fontStyle, text, color, false);
		};
		~SpriteText();
        bool LoadFromRenderedText( TTF_Font * font, std::string textureText, SDL_Color textColor, bool wrapped );
    protected:
        int wrappedLength = 800;
};

#endif // SPRITETEXT_H
