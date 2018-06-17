#include "score-view.h"

ScoreView::ScoreView(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->font_style = TTF_OpenFont( this->DISPLAY_FONT.c_str(), 18 );

    if (this->font_style == NULL)
    {
        Logger::getInstance()->error(string("No se pudo cargar la fuente del score. SDL_TTF Error: ") + TTF_GetError());
    }

}

ScoreView::~ScoreView()
{
    Logger::getInstance()->debug("DESTRUYENDO SCORE VIEW");
    TTF_CloseFont(this->font_style);
}

void ScoreView::RenderRedTeamScore(Team* team)
{

    std::string goals = std::to_string(team->GetGoals());

    SDL_Color text_color = { 255, 255, 255, 0xFF };
    SDL_Surface* surface = TTF_RenderText_Solid(this->font_style, goals.c_str(), text_color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_Rect rect;

    rect.x = 42;
    rect.y = 40;
    rect.w = 25;
    rect.h = 25;

    SDL_RenderCopy(this->renderer, message, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}

void ScoreView::RenderGreenTeamScore(Team* team)
{

    std::string goals = std::to_string(team->GetGoals());

    SDL_Color text_color = { 255, 255, 255, 0xFF };
    SDL_Surface* surface = TTF_RenderText_Solid(this->font_style, goals.c_str(), text_color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_Rect rect;

    rect.x = 144;
    rect.y = 40;
    rect.w = 25;
    rect.h = 25;

    SDL_RenderCopy(this->renderer, message, NULL, &rect);

    SDL_RenderCopy(this->renderer, message, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}

void ScoreView::Render(Team* team_a, Team* team_b)
{
    // TODO => VER QUE EL A PUEDE ESTAR USANDO LA VERDE Y EL B LA ROJA
    this->RenderRedTeamScore(team_a);
    this->RenderGreenTeamScore(team_b);
}


