#include "score-view.h"

ScoreView::ScoreView(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->font_style = TTF_OpenFont( this->DISPLAY_FONT.c_str(), 25 );
    this->title_font_style = TTF_OpenFont( this->DISPLAY_FONT.c_str(), 17.5 );

    if (this->font_style == NULL || this->title_font_style == NULL)
    {
        Logger::getInstance()->error(string("No se pudo cargar la fuente del score. SDL_TTF Error: ") + TTF_GetError());
    }

}

ScoreView::~ScoreView()
{
    Logger::getInstance()->debug("DESTRUYENDO SCORE VIEW");
    TTF_CloseFont(this->font_style);
    TTF_CloseFont(this->title_font_style);
}

void ScoreView::RenderTitle()
{

    std::string team = "TeamA";

    SDL_Color text_color = { 255, 0, 0, 0xFF };
    SDL_Surface* surface = TTF_RenderText_Solid(this->title_font_style, team.c_str(), text_color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_Rect rect;

    rect.x = 12;
    rect.y = 5;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopy(this->renderer, message, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);

    team = "TeamB";

    text_color = { 127, 255, 0, 0xFF };
    surface = TTF_RenderText_Solid(this->title_font_style, team.c_str(), text_color);
    message = SDL_CreateTextureFromSurface(this->renderer, surface);

    rect.x = 119;

    SDL_RenderCopy(this->renderer, message, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}

void ScoreView::RenderTeamAScore(Team* team)
{

    std::string goals = std::to_string(team->GetGoals());

    SDL_Color text_color = { 255, 255, 255, 0xFF };
    SDL_Surface* surface = TTF_RenderText_Solid(this->font_style, goals.c_str(), text_color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_Rect rect;

    rect.x = 42;
    rect.y = 40;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopy(this->renderer, message, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}

void ScoreView::RenderTeamBScore(Team* team)
{

    std::string goals = std::to_string(team->GetGoals());

    SDL_Color text_color = { 255, 255, 255, 0xFF };
    SDL_Surface* surface = TTF_RenderText_Solid(this->font_style, goals.c_str(), text_color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_Rect rect;

    rect.x = 144;
    rect.y = 40;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopy(this->renderer, message, NULL, &rect);

    SDL_RenderCopy(this->renderer, message, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}

void ScoreView::Render(Team* team_a, Team* team_b)
{
    this->RenderTitle();
    this->RenderTeamAScore(team_a);
    this->RenderTeamBScore(team_b);
}

