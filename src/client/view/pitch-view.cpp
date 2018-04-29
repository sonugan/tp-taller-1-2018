#include "pitch-view.h"
#include "../../shared/logger.h"


PitchView::PitchView(Pitch* pitch, SDL_Renderer* renderer)
{
    this->pitch = pitch;
    this->renderer = renderer;

    SDL_Rect* sprite1 = new SDL_Rect();
    sprite1->x = 0;
    sprite1->y =   0;
    sprite1->w =  800;
    sprite1->h = 600;

    std::vector<SDL_Rect*> clips;
    clips.push_back(sprite1);

    animations.push_back(new Animation("pitch", clips));
    current_animation_index = 0;

	this->sprite_sheet = new SpriteSheet(renderer, "pitch.jpg");
}

PitchView::~PitchView()
{
    Logger::getInstance()->debug("DESTRUYENDO LA VISTA DEL CAMPO");
    delete sprite_sheet;

    for (unsigned int i = 0; i < animations.size(); i++) {
        delete (animations[i]);
    }
}

void PitchView::Render(int x_camera, int y_camera, int max_x, int max_y)
{
    SDL_Rect* current_clip = this->animations[current_animation_index]->NextClip();
    current_clip->x = x_camera;
    current_clip->y = y_camera;
    sprite_sheet->Render( 0, 0, current_clip );
}
