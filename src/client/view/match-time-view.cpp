#include "match-time-view.h"

MatchTimeView::MatchTimeView(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->font_style = TTF_OpenFont( this->DISPLAY_FONT.c_str(), 18 );

    if (this->font_style == NULL)
    {
        Logger::getInstance()->error(string("No se pudo cargar la fuente del match time. SDL_TTF Error: ") + TTF_GetError());
    }
}

MatchTimeView::~MatchTimeView()
{
    Logger::getInstance()->debug("DESTRUYENDO MATCH TIME VIEW");
    TTF_CloseFont(this->font_style);
}

void MatchTimeView::Render(MATCH_TIME_TYPE match_time)
{
    char* time = "";

    if (match_time == MATCH_TIME_TYPE::FIRST_TIME)
    {
        time = "1T";
    }
    else
    {
        time = "2T";
    }

    SDL_Color text_color = { 237, 41, 57, 0xFF };
    SDL_Surface* surface = TTF_RenderText_Solid(this->font_style, time, text_color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_Rect rect;

    rect.x = 658;
    rect.y = 41;
    rect.w = 30;
    rect.h = 30;

    SDL_RenderCopy(this->renderer, message, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}



