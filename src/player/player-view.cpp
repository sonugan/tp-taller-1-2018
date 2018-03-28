#include "player-view.h"

PlayerView::PlayerView(Player* player, SDL_Renderer* renderer)
{
    this->width = 64;
    this->height = 205;

    this->frame = 0;
    this->player = player;
    this->renderer = renderer;

    SDL_Rect* sprite1 = new SDL_Rect();
    sprite1->x =   0;
    sprite1->y =   0;
    sprite1->w =  64;
    sprite1->h = 205;

    SDL_Rect* sprite2 = new SDL_Rect();
    sprite2->x =  64;
    sprite2->y =   0;
    sprite2->w =  64;
    sprite2->h = 205;

    SDL_Rect* sprite3 = new SDL_Rect();
    sprite3->x = 128;
    sprite3->y =   0;
    sprite3->w =  64;
    sprite3->h = 205;


    SDL_Rect* sprite4 = new SDL_Rect();
    sprite4->x = 196;
    sprite4->y =   0;
    sprite4->w =  64;
    sprite4->h = 205;

    std::vector<SDL_Rect*> clips;
    clips.push_back(sprite1);
    clips.push_back(sprite2);
    clips.push_back(sprite3);
    clips.push_back(sprite4);

	this->sprite_sheet = new SpriteSheet(renderer, "foo.png", clips);

}

PlayerView::~PlayerView() {
    std::cout << "Destructor de PlayerView" << "\n";
    delete sprite_sheet;
}

void PlayerView::Render() {
//    ++frame;
//    if ((frame * FRAMES_PER_EVENT) >= WALKING_ANIMATION_FRAMES) {
//        frame = 0;
//    }
//    int current_frame_index = frame * FRAMES_PER_EVENT;
//    SDL_Rect* currentClip = this->sprite_sheet->GetClips()[current_frame_index];
//
//    int x = player->GetLocation()->GetX() - this->camera->area->x;
//    int y = player->GetLocation()->GetY() - this->camera->area->y;
//
//    if(x < 0)
//    {
//        x = 0;
//    }
//
//    if(y < 0)
//    {
//        y = 0;
//    }
//
//    if(x > 800 - this->width)
//    {
//        x = 800 - this->width;
//    }
//
//    if(y > 600 - this->height)
//    {
//        y = 600 - this->height;
//    }
//    std::cout << y << "\n";
//
//    sprite_sheet->Render( x, y, currentClip );
    //sprite_sheet->Render( player->GetLocation()->GetX(), player->GetLocation()->GetY(), currentClip );
    //sprite_sheet->Render( 0, 0, currentClip );
}

void PlayerView::Render(int xCamera, int yCamera, int maxX, int maxY)
{
    std::cout << maxX << "\n";
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

    sprite_sheet->Render( x, y, currentClip );
}

Location* PlayerView::GetLocation()
{
    return this->player->GetLocation();
}
