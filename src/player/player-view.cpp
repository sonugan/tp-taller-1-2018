#include "player-view.h"

PlayerView::PlayerView(Player* player, SDL_Renderer* renderer)
{
    this->width = 62;
    this->height = 62;

    this->frame = 0;
    this->player = player;
    this->renderer = renderer;

    SDL_Rect* sprite1 = new SDL_Rect();
    sprite1->x = 1;
    sprite1->y = 128;
    sprite1->w = this->width;
    sprite1->h = this->height;

    SDL_Rect* sprite2 = new SDL_Rect();
    sprite2->x = 64;
    sprite2->y = 128;
    sprite2->w = this->width;
    sprite2->h = this->height;

    SDL_Rect* sprite3 = new SDL_Rect();
    sprite3->x = 128;
    sprite3->y = 128;
    sprite3->w = this->width;
    sprite3->h = this->height;

    SDL_Rect* sprite4 = new SDL_Rect();
    sprite4->x = 192;
    sprite4->y = 128;
    sprite4->w = this->width;
    sprite4->h = this->height;

    std::vector<SDL_Rect*> clips;
    clips.push_back(sprite1);
    clips.push_back(sprite2);
    clips.push_back(sprite3);
    clips.push_back(sprite4);

	this->sprite_sheet = new SpriteSheet(renderer, "player.png", clips);

}

PlayerView::~PlayerView() {
    std::cout << "Destructor de PlayerView" << "\n";
    delete sprite_sheet;
}

void PlayerView::Render() {
    int current_frame_index = frame * FRAMES_PER_EVENT;
    SDL_Rect* currentClip = this->sprite_sheet->GetClips()[current_frame_index];

    sprite_sheet->Render( 0, 0, currentClip );
}

void PlayerView::Render(int xCamera, int yCamera, int maxX, int maxY)
{
    ++frame;
    if ((frame * FRAMES_PER_EVENT) >= WALKING_ANIMATION_FRAMES) {
        frame = 0;
    }
    int current_frame_index = frame * FRAMES_PER_EVENT;
    SDL_Rect* currentClip = this->sprite_sheet->GetClips()[current_frame_index];

    int x = player->GetLocation()->GetX() - xCamera;
    int y = player->GetLocation()->GetY() - yCamera;

    if(x < 0)
    {
        x = 0;
    }

    if(y < 0)
    {
        y = 0;
    }

    if(x > maxX - this->width)
    {
        x = maxX - this->width;
    }

    if(y > maxY - this->height)
    {
        y = maxY - this->height;
    }

    DIRECTION direction = this->player->GetDirection();
    switch(direction)
    {
        case NORTH:
            angle = 0;
        break;
        case WEST:
            angle = -90;
        break;
        case SOUTH:
            angle = 180;
        break;
        case EAST:
            angle = 90;
        break;
        case NORTHEAST:
            angle = 45;
        break;
        case NORTHWEST:
            angle = -45;
        break;
        case SOUTHEAST:
            angle = 135;
        break;
        case SOUTHWEST:
            angle = -135;
        break;
        default:
            angle = angle;
        break;
    }
    sprite_sheet->Render( x, y, currentClip, this->angle);
}

Location* PlayerView::GetLocation()
{
    return this->player->GetLocation();
}

