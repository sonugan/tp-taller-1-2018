#include "info-panel-view.h"

InfoPanelView::InfoPanelView()
{
    SDL_Rect* sprite1 = new SDL_Rect();
    sprite1->x = 0;
    sprite1->y = 0;
    sprite1->w = this->SPRITE_WIDTH;
    sprite1->h = this->SPRITE_HEIGHT;

    std::vector<SDL_Rect*> clips;
    clips.push_back(sprite1);

    animations.push_back(new Animation("info-panel", clips));
    current_animation_index = 0;

	this->sprite_sheet = SpritesProvider::GetDefaultSheet(INFO_PANEL_BACK);
}

InfoPanelView::~InfoPanelView()
{
    Logger::getInstance()->debug("DESTRUYENDO PANEL DE INFO");

    for (unsigned int i = 0; i < animations.size(); i++) {
        delete (animations[i]);
    }
}

void InfoPanelView::Render(int x_camera, int y_camera, int max_x, int max_y)
{
    SDL_Rect* current_clip = this->animations[current_animation_index]->NextClip();
    current_clip->x = x_camera;
    current_clip->y = 0;
    sprite_sheet->Render( 0, 0, current_clip );
}

