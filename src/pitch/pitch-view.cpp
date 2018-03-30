#include "pitch-view.h"

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
    currentAnimationIndex = 0;

	this->sprite_sheet = new SpriteSheet(renderer, "pitch.jpg", clips);
}

PitchView::~PitchView()
{
    std::cout << "Destructor de PitchView" << "\n";
    delete sprite_sheet;

    for (unsigned int i = 0; i < animations.size(); i++) {
        delete (animations[i]);
    }
}

void PitchView::Render() {
    SDL_Rect* currentClip = this->animations[currentAnimationIndex]->NextClip();
    sprite_sheet->Render( 0, 0, currentClip );
}

void PitchView::Render(int xCamera, int yCamera, int maxX, int maxY)
{
    SDL_Rect* currentClip = this->sprite_sheet->GetClips()[0];
    currentClip->x = xCamera;
    currentClip->y = yCamera;
    sprite_sheet->Render( 0, 0, currentClip );
}
