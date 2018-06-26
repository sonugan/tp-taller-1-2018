#ifndef SCOREVIEW_H
#define SCOREVIEW_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../shared/model/team.h"
#include "../../shared/logger.h"

class ScoreView
{
    public:
        ScoreView(SDL_Renderer* renderer);
        virtual ~ScoreView();
        void Free();
        void Render(Team* team_a, Team* team_b);
    protected:
        std::string DISPLAY_FONT = "src/client/sprites/tehkan_world_cup.ttf";
        TTF_Font* font_style = NULL;
        TTF_Font* title_font_style = NULL;
        SDL_Renderer* renderer;
    private:
        bool title_renderized = false;
        void RenderTeamAScore(Team* team);
        void RenderTeamBScore(Team* team);
        void RenderTitle();
};

#endif // SCOREVIEW_H
