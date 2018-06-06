#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../shared/logger.h"
#include "../../shared/model/timer.h"

class TimerView
{
    public:
        TimerView(SDL_Renderer* renderer);
        virtual ~TimerView();
        void Free();
        void Render(Timer* timer);
    protected:
        std::string DISPLAY_FONT = "src/client/sprites/tehkan_world_cup.ttf";
        TTF_Font* font_style = NULL;
        SDL_Renderer* renderer;
    private:
};

#endif // TIMER-VIEW_H
