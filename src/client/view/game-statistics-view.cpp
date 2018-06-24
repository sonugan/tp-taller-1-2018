#include "game-statistics-view.h"

GameStatisticsView::GameStatisticsView(SDL_Renderer* renderer)
{
    SDL_Rect* sprite1 = new SDL_Rect();
    sprite1->x = 0;
    sprite1->y = 0;
    sprite1->w = 800;
    sprite1->h = 600;

    std::vector<SDL_Rect*> clips;
    clips.push_back(sprite1);

    animations.push_back(new Animation("game_statistics", clips));

	this->sprite_sheet = SpritesProvider::GetDefaultSheet(GAME_STATISTICS);

    this->renderer = renderer;
    this->font_style = TTF_OpenFont( this->DISPLAY_FONT.c_str(), 20 );

    if (this->font_style == NULL)
    {
        Logger::getInstance()->error(string("No se pudo cargar la fuente de las estadisticas. SDL_TTF Error: ") + TTF_GetError());
    }

}

GameStatisticsView::~GameStatisticsView()
{
    Logger::getInstance()->debug("DESTRUYENDO GAME STATISTICS VIEW");
    delete (animations[0]);
    TTF_CloseFont(this->font_style);
}

void GameStatisticsView::RenderTeamScores(Team* team_a, Team* team_b)
{
    std::string goals = "Team A: " + std::to_string(team_a->GetGoals()) + " / Team B: " + std::to_string(team_b->GetGoals());

    SDL_Color text_color = { 255, 255, 255, 0xFF };
    SDL_Surface* surface = TTF_RenderText_Solid(this->font_style, goals.c_str(), text_color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_Rect rect;

    rect.x = 180;
    rect.y = 180;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopy(this->renderer, message, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}

void GameStatisticsView::Render(Team* team_a, Team* team_b)
{
    SDL_Rect* current_clip = this->animations[0]->NextClip();
    current_clip->x = 0;
    current_clip->y = 0;
    sprite_sheet->Render( 0, 0, current_clip);

    RenderTeamScores(team_a, team_b);
}
