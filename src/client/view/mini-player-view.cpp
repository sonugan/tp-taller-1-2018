#include "mini-player-view.h"

MiniPlayerView::MiniPlayerView(Player* player, int real_pitch_height, int real_pitch_width)
{
    this->player = player;
    this->real_pitch_height = real_pitch_height;
    this->real_pitch_width = real_pitch_width;

    SDL_Rect* sprite1 = new SDL_Rect();
    sprite1->x = 0;
    sprite1->y =  0;
    sprite1->w =  7;
    sprite1->h = 7;

    std::vector<SDL_Rect*> clips;
    clips.push_back(sprite1);

    animations.push_back(new Animation("mini-player", clips));
    current_animation_index = 0;

    if (player->PlaysForTeamA())
    {
        this->sprite_sheet = SpritesProvider::GetDefaultSheet(TEAM_A_MINI_PLAYER);
    }
    else
    {
        this->sprite_sheet = SpritesProvider::GetDefaultSheet(TEAM_B_MINI_PLAYER);
    }
}

MiniPlayerView::~MiniPlayerView()
{
    Logger::getInstance()->debug("DESTRUYENDO MINI PLAYER");

    for (unsigned int i = 0; i < animations.size(); i++)
    {
        delete (animations[i]);
    }
}

int MiniPlayerView::GetMiniPlayerX()
{
    int mini_x = this->player->GetLocation()->GetX() * MINI_PITCH_WIDTH;
    mini_x = mini_x / this->real_pitch_width;
    return mini_x + MINI_PITCH_OFFSET_X;
}

int MiniPlayerView::GetMiniPlayerY()
{
    int mini_y = this->player->GetLocation()->GetY() * MINI_PITCH_HEIGHT;
    mini_y = mini_y / this->real_pitch_height;
    return mini_y + MINI_PITCH_OFFSET_Y;
}

void MiniPlayerView::Render(int x_camera, int y_camera, int max_x, int max_y)
{
    SDL_Rect* current_clip = this->animations[current_animation_index]->NextClip();
    sprite_sheet->Render(this->GetMiniPlayerX(), this->GetMiniPlayerY(), current_clip);
}


