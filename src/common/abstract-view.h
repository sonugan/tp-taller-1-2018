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
        virtual void Render(int x_camera, int y_camera, int max_x, int max_y) = 0;
        virtual ~AbstractView () {};

    protected:
        SDL_Renderer* renderer;
        SpriteSheet* sprite_sheet;
        virtual void SetAnimation(Animation* animation) {};
        std::vector<Animation*> animations;
        int current_animation_index = 0;
};

#endif // ABSTRACTVIEW_H
