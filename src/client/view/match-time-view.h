#ifndef MATCHTIMEVIEW_H
#define MATCHTIMEVIEW_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../shared/model/match-time-type.h"
#include "../../shared/logger.h"

class MatchTimeView
{
    public:
        MatchTimeView(SDL_Renderer* renderer);
        virtual ~MatchTimeView();
        void Free();
        void Render(MATCH_TIME_TYPE match_time);
    protected:
        std::string DISPLAY_FONT = "src/client/sprites/tehkan_world_cup.ttf";
        TTF_Font* font_style = NULL;
        SDL_Renderer* renderer;
    private:
};

#endif // MatchTimeView_H
