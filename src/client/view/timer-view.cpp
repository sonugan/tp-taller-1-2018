#include "timer-view.h"

TimerView::TimerView(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->font_style = TTF_OpenFont( this->DISPLAY_FONT.c_str(), 18 );

    if (this->font_style == NULL)
    {
        Logger::getInstance()->error(string("No se pudo cargar la fuente del timer. SDL_TTF Error: ") + TTF_GetError());
    }

}

TimerView::~TimerView()
{
    Logger::getInstance()->debug("DESTRUYENDO TIMER VIEW");
    TTF_CloseFont(this->font_style);
}

void TimerView::Render(std::string remaining_time)
{
    SDL_Color text_color = { 255, 255, 255, 0xFF };
    SDL_Surface* surface = TTF_RenderText_Solid(this->font_style, remaining_time.c_str(), text_color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_Rect rect;

    rect.x = 710;
    rect.y = 40;
    rect.w = 80;
    rect.h = 30;

    SDL_RenderCopy(this->renderer, message, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);

}

