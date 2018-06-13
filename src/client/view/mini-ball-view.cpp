#include "mini-ball-view.h"


MiniBallView::MiniBallView(Ball* ball, int real_pitch_height, int real_pitch_width)
{
    this->ball = ball;
    this->real_pitch_height = real_pitch_height;
    this->real_pitch_width = real_pitch_width;

    SDL_Rect* sprite1 = new SDL_Rect();
    sprite1->x = 0;
    sprite1->y =  0;
    sprite1->w =  MINI_BALL_WIDTH;
    sprite1->h = MINI_BALL_HEIGHT;

    std::vector<SDL_Rect*> clips;
    clips.push_back(sprite1);

    animations.push_back(new Animation("mini-ball", clips));
    current_animation_index = 0;
    this->sprite_sheet = SpritesProvider::GetDefaultSheet(MINI_BALL);
}

MiniBallView::~MiniBallView()
{
    Logger::getInstance()->debug("DESTRUYENDO MINI BALL SELECTOR");

    for (unsigned int i = 0; i < animations.size(); i++)
    {
        delete (animations[i]);
    }
}

int MiniBallView::GetMiniBallX()
{
    int mini_x = this->ball->GetLocation()->GetX() * MINI_PITCH_WIDTH;
    mini_x = mini_x / this->real_pitch_width;
    mini_x = mini_x + MINI_PITCH_OFFSET_X;
    mini_x = mini_x - MINI_BALL_X_MARGIN;
    return mini_x;
}

int MiniBallView::GetMiniBallY()
{
    int mini_y = this->ball->GetLocation()->GetY() * MINI_PITCH_HEIGHT;
    mini_y = mini_y / this->real_pitch_height;
    mini_y = mini_y + MINI_PITCH_OFFSET_Y;
    mini_y = mini_y - MINI_BALL_Y_MARGIN;
    return mini_y;
}

void MiniBallView::Render(int x_camera, int y_camera, int max_x, int max_y)
{
    SDL_Rect* current_clip = this->animations[current_animation_index]->NextClip();
    sprite_sheet->Render(this->GetMiniBallX(), this->GetMiniBallY(), current_clip);
}


