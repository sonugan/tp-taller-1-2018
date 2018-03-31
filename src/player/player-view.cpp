#include "player-view.h"

PlayerView::PlayerView(Player* player, SDL_Renderer* renderer)
{
    this->width = 62;
    this->height = 62;

    this->frame = 0;
    this->player = player;
    this->renderer = renderer;

    std::vector<SDL_Rect*> runClips;

    //Run sprites
    SDL_Rect* runSprite1 = new SDL_Rect();
    runSprite1->x = 1;
    runSprite1->y = 128;
    runSprite1->w = this->width;
    runSprite1->h = this->height;
    runClips.push_back(runSprite1);

    SDL_Rect* runSprite2 = new SDL_Rect();
    runSprite2->x = 64;
    runSprite2->y = 128;
    runSprite2->w = this->width;
    runSprite2->h = this->height;
    runClips.push_back(runSprite2);

    SDL_Rect* runSprite3 = new SDL_Rect();
    runSprite3->x = 128;
    runSprite3->y = 128;
    runSprite3->w = this->width;
    runSprite3->h = this->height;
    runClips.push_back(runSprite3);

    SDL_Rect* runSprite4 = new SDL_Rect();
    runSprite4->x = 192;
    runSprite4->y = 128;
    runSprite4->w = this->width;
    runSprite4->h = this->height;
    runClips.push_back(runSprite4);

    animations.push_back(new Animation("run", runClips, FRAMES_PER_EVENT));

    std::vector<SDL_Rect*> stillClips;

    //Still sprites
    SDL_Rect* stillSprite1 = new SDL_Rect();
    stillSprite1->x = 1;
    stillSprite1->y = 1;
    stillSprite1->w = this->width;
    stillSprite1->h = this->height;
    stillClips.push_back(stillSprite1);

    SDL_Rect* stillSprite2 = new SDL_Rect();
    stillSprite2->x = 64;
    stillSprite2->y = 1;
    stillSprite2->w = this->width;
    stillSprite2->h = this->height;
    stillClips.push_back(stillSprite2);

    SDL_Rect* stillSprite3 = new SDL_Rect();
    stillSprite3->x = 128;
    stillSprite3->y = 1;
    stillSprite3->w = this->width;
    stillSprite3->h = this->height;
    stillClips.push_back(stillSprite3);

    SDL_Rect* stillSprite4 = new SDL_Rect();
    stillSprite4->x = 192;
    stillSprite4->y = 1;
    stillSprite4->w = this->width;
    stillSprite4->h = this->height;
    stillClips.push_back(stillSprite4);

    animations.push_back(new Animation("still", stillClips, FRAMES_PER_EVENT));

    currentAnimationIndex = 0;

    Location* currentLocation = player->GetLocation();
    previousLocation = new Location(currentLocation->GetX(), currentLocation->GetY(), currentLocation->GetZ());

	this->sprite_sheet = new SpriteSheet(renderer, "player.png", runClips);
}

PlayerView::~PlayerView() {
    std::cout << "Destructor de PlayerView" << "\n";
    delete sprite_sheet;

    //TODO: delete clips in animation destructor
    for (unsigned int i = 0; i < animations.size(); i++) {
        delete (animations[i]);
    }
    delete previousLocation;
}

void PlayerView::Render(int xCamera, int yCamera, int maxX, int maxY)
{
    if(IsStill())
    {
        currentAnimationIndex = STILL_ANIMATION_INDEX;
    }
    else
    {
        currentAnimationIndex = RUN_ANIMATION_INDEX;
    }

    this->previousLocation->UpdateX(player->GetLocation()->GetX());
    this->previousLocation->UpdateY(player->GetLocation()->GetY());

    SDL_Rect* currentClip = animations[currentAnimationIndex]->NextClip();

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

void PlayerView::SetAnimation(Animation* animation)
{

}

bool PlayerView::IsStill()
{
    Location* currentLocation = player->GetLocation();
    return currentLocation->GetX() == previousLocation->GetX()
        && currentLocation->GetY() == previousLocation->GetY();
}
