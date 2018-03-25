#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite-sheet.h"

class AbstractView
{
    public:
        virtual void Render() = 0;
        virtual ~AbstractView () {};

    protected:
        SDL_Renderer* renderer;
        SpriteSheet* sprite_sheet;
};

#endif // ABSTRACTVIEW_H
