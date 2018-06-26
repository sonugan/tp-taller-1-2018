#ifndef GAME-STATISTICS-VIEW_H
#define GAME-STATISTICS-VIEW_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include "../../shared/model/team.h"
#include "../../shared/logger.h"

class GameStatisticsView
{
public:
    GameStatisticsView(SDL_Renderer* renderer);
    virtual ~GameStatisticsView();
    void Render(Team* team_a, Team* team_b, map<string, int> user_scores);
protected:
    std::string DISPLAY_FONT = "src/client/sprites/tehkan_world_cup.ttf";
    TTF_Font* font_style = NULL;
    SDL_Renderer* renderer;
    SpriteSheet* sprite_sheet;
    std::vector<Animation*> animations;
private:
    void RenderScoreBoard(map<string, int> user_scores);
    void RenderTeamScores(Team* team_a, Team* team_b);
};

#endif // GAME-STATISTICS-VIEW_H
