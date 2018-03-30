#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite-sheet.h"
#include "animation.h"

class AbstractView
{
    public:
        virtual void Render() = 0;
        virtual void Render(int xCamera, int yCamera, int maxX, int maxY) = 0;
        virtual ~AbstractView () {};

    protected:
        SDL_Renderer* renderer;
        SpriteSheet* sprite_sheet;
        virtual void SetAnimation(Animation* animation) {};
        std::vector<Animation*> animations;
        int currentAnimationIndex = 0;
};

#endif // ABSTRACTVIEW_H
