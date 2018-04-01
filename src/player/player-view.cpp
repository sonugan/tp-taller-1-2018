#include "player-view.h"

PlayerView::PlayerView(Player* player, SDL_Renderer* renderer)
{
    this->width = 62;
    this->height = 62;

    this->frame = 0;
    this->player = player;
    this->renderer = renderer;

    std::vector<SDL_Rect*> run_clips;

    //Run sprites
    SDL_Rect* run_sprite_1 = new SDL_Rect();
    run_sprite_1->x = 0;
    run_sprite_1->y = 128;
    run_sprite_1->w = this->width;
    run_sprite_1->h = this->height;
    run_clips.push_back(run_sprite_1);

    SDL_Rect* run_sprite_2 = new SDL_Rect();
    run_sprite_2->x = 64;
    run_sprite_2->y = 128;
    run_sprite_2->w = this->width;
    run_sprite_2->h = this->height;
    run_clips.push_back(run_sprite_2);

    SDL_Rect* run_sprite_3 = new SDL_Rect();
    run_sprite_3->x = 128;
    run_sprite_3->y = 128;
    run_sprite_3->w = this->width;
    run_sprite_3->h = this->height;
    run_clips.push_back(run_sprite_3);

    SDL_Rect* run_sprite_4 = new SDL_Rect();
    run_sprite_4->x = 192;
    run_sprite_4->y = 128;
    run_sprite_4->w = this->width;
    run_sprite_4->h = this->height;
    run_clips.push_back(run_sprite_4);

    animations.push_back(new Animation("run", run_clips, FRAMES_PER_EVENT));

    std::vector<SDL_Rect*> still_clips;

    //Still sprites
    SDL_Rect* still_sprite_1 = new SDL_Rect();
    still_sprite_1->x = 0;
    still_sprite_1->y = 1;
    still_sprite_1->w = this->width;
    still_sprite_1->h = this->height;
    still_clips.push_back(still_sprite_1);

    SDL_Rect* still_sprite_2 = new SDL_Rect();
    still_sprite_2->x = 64;
    still_sprite_2->y = 1;
    still_sprite_2->w = this->width;
    still_sprite_2->h = this->height;
    still_clips.push_back(still_sprite_2);

    SDL_Rect* still_sprite_3 = new SDL_Rect();
    still_sprite_3->x = 128;
    still_sprite_3->y = 1;
    still_sprite_3->w = this->width;
    still_sprite_3->h = this->height;
    still_clips.push_back(still_sprite_3);

    SDL_Rect* still_sprite_4 = new SDL_Rect();
    still_sprite_4->x = 192;
    still_sprite_4->y = 1;
    still_sprite_4->w = this->width;
    still_sprite_4->h = this->height;
    still_clips.push_back(still_sprite_4);

    animations.push_back(new Animation("still", still_clips, FRAMES_PER_EVENT));

    current_animation_index = 0;

    Location* current_location = player->GetLocation();
    previous_location = new Location(current_location->GetX(), current_location->GetY(), current_location->GetZ());

	this->sprite_sheet = new SpriteSheet(renderer, "player.png", run_clips);
}

PlayerView::~PlayerView() {
    std::cout << "Destructor de PlayerView" << "\n";
    delete sprite_sheet;

    //TODO: delete clips in animation destructor
    for (unsigned int i = 0; i < animations.size(); i++) {
        delete (animations[i]);
    }
    delete previous_location;
}

void PlayerView::Render(int x_camera, int y_camera, int max_x, int max_y) {
    if(IsStill()) {
        current_animation_index = STILL_ANIMATION_INDEX;
        angle = 90;
    } else {
        current_animation_index = RUN_ANIMATION_INDEX;
            DIRECTION direction = this->player->GetDirection();
        switch(direction) {
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
    }
    SDL_Rect* current_clip = animations[current_animation_index]->NextClip();
    int x, y;

    this->previous_location->UpdateX(player->GetLocation()->GetX());
    this->previous_location->UpdateY(player->GetLocation()->GetY());

    x = player->GetLocation()->GetX() - x_camera;
    y = player->GetLocation()->GetY() - y_camera;

    if (player->IsSelected()) {

        if(x < 0) {
            x = 0;
        }

        if(y < 0) {
            y = 0;
        }

        if(x > max_x - this->width) {
            x = max_x - this->width;
        }

        if(y > max_y - this->height) {
            y = max_y - this->height;
        }
    }



    sprite_sheet->Render( x, y, current_clip, this->angle);
}

Location* PlayerView::GetLocation()
{
    return this->player->GetLocation();
}

void PlayerView::SetAnimation(Animation* animation)
{

}

bool PlayerView::IsStill()
{
    Location* current_location = player->GetLocation();
    bool still = current_location->GetX() == previous_location->GetX()
        && current_location->GetY() == previous_location->GetY();
    return still;
}
