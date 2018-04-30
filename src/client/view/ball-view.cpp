#include "ball-view.h"

BallView::BallView(Ball* ball, SDL_Renderer* renderer)
{
    this->ball = ball;
    this->renderer = renderer;

    SDL_Rect* sprite1 = new SDL_Rect();
    sprite1->x = 0;
    sprite1->y =   0;
    sprite1->w =  32;
    sprite1->h = 32;

    std::vector<SDL_Rect*> clips;
    clips.push_back(sprite1);

    animations.push_back(new Animation("ball", clips));
    current_animation_index = 0;

	this->sprite_sheet = new SpriteSheet(renderer, "ball.png");
}

BallView::~BallView()
{
    //dtor
}

void BallView::Render(int x_camera, int y_camera, int max_x, int max_y) {
    SDL_Rect* current_clip = this->animations[current_animation_index]->NextClip();

    int x, y;

    x = ball->GetLocation()->GetX() - x_camera;
    y = ball->GetLocation()->GetY() - y_camera;

    sprite_sheet->Render( x, y, current_clip );
}
