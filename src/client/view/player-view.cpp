#include "player-view.h"
#include "../../shared/logger.h"

PlayerView::PlayerView(Player* player)
{
    this->width = 62;
    this->height = 62;

    this->frame = 0;
    this->player = player;

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

    std::vector<SDL_Rect*> kick_clips;

    // Kick sprites
    SDL_Rect* kick_sprite_1 = new SDL_Rect();
    kick_sprite_1->x = 128;
    kick_sprite_1->y = 192;
    kick_sprite_1->w = this->width;
    kick_sprite_1->h = this->height;
    kick_clips.push_back(kick_sprite_1);

    SDL_Rect* kick_sprite_2 = new SDL_Rect();
    kick_sprite_2->x = 64;
    kick_sprite_2->y = 192;
    kick_sprite_2->w = this->width;
    kick_sprite_2->h = this->height;
    kick_clips.push_back(kick_sprite_2);

    SDL_Rect* kick_sprite_3 = new SDL_Rect();
    kick_sprite_3->x = 128;
    kick_sprite_3->y = 192;
    kick_sprite_3->w = this->width;
    kick_sprite_3->h = this->height;
    kick_clips.push_back(kick_sprite_3);

    SDL_Rect* kick_sprite_4 = new SDL_Rect();
    kick_sprite_4->x = 192;
    kick_sprite_4->y = 192;
    kick_sprite_4->w = this->width;
    kick_sprite_4->h = this->height;
    kick_clips.push_back(kick_sprite_4);

    animations.push_back(new Animation("kick", kick_clips, FRAMES_PER_EVENT));

    std::vector<SDL_Rect*> recover_ball_clips;

    // Recovering ball sprites
    SDL_Rect* recover_sprite_1 = new SDL_Rect();
    recover_sprite_1->x = 0;
    recover_sprite_1->y = 448;
    recover_sprite_1->w = this->width;
    recover_sprite_1->h = this->height;
    recover_ball_clips.push_back(recover_sprite_1);

    SDL_Rect* recover_sprite_2 = new SDL_Rect();
    recover_sprite_2->x = 0;
    recover_sprite_2->y = 448;
    recover_sprite_2->w = this->width;
    recover_sprite_2->h = this->height;
    recover_ball_clips.push_back(recover_sprite_2);

    SDL_Rect* recover_sprite_3 = new SDL_Rect();
    recover_sprite_3->x = 0;
    recover_sprite_3->y = 448;
    recover_sprite_3->w = this->width;
    recover_sprite_3->h = this->height;
    recover_ball_clips.push_back(recover_sprite_3);

    SDL_Rect* recover_sprite_4 = new SDL_Rect();
    recover_sprite_4->x = 64;
    recover_sprite_4->y = 448;
    recover_sprite_4->w = this->width;
    recover_sprite_4->h = this->height;
    recover_ball_clips.push_back(recover_sprite_4);

    SDL_Rect* recover_sprite_5 = new SDL_Rect();
    recover_sprite_5->x = 128;
    recover_sprite_5->y = 448;
    recover_sprite_5->w = this->width;
    recover_sprite_5->h = this->height;
    recover_ball_clips.push_back(recover_sprite_5);

    SDL_Rect* recover_sprite_6 = new SDL_Rect();
    recover_sprite_6->x = 128;
    recover_sprite_6->y = 448;
    recover_sprite_6->w = this->width;
    recover_sprite_6->h = this->height;
    recover_ball_clips.push_back(recover_sprite_6);

    SDL_Rect* recover_sprite_7 = new SDL_Rect();
    recover_sprite_7->x = 192;
    recover_sprite_3->y = 448;
    recover_sprite_7->w = this->width;
    recover_sprite_7->h = this->height;
    recover_ball_clips.push_back(recover_sprite_7);

    animations.push_back(new Animation("recover", recover_ball_clips, FRAMES_PER_EVENT));

    current_animation_index = 0;

    std::vector<SDL_Rect*> player_selector_clips;

    //player selector sprites
    SDL_Rect* player_selector_sprite_1 = new SDL_Rect();
    player_selector_sprite_1->x = 0;
    player_selector_sprite_1->y = 1;
    player_selector_sprite_1->w = this->width;
    player_selector_sprite_1->h = this->height;
    player_selector_clips.push_back(player_selector_sprite_1);

    animations.push_back(new Animation("selector", player_selector_clips, FRAMES_PER_EVENT));

    Location* current_location = player->GetLocation();
    previous_location = new Location(current_location->GetX(), current_location->GetY(), current_location->GetZ());

    string kitFile = player->GetTeam()->GetName();
    kitFile.append("/");
    kitFile.append(player->GetTeam()->GetShirt());
    kitFile.append("-kit.png");

    if (player->PlaysForTeamA())
    {
        this->sprite_sheet = SpritesProvider::GetSheet(TEAM_A_PLAYER, kitFile);
    }
    else
    {
        this->sprite_sheet = SpritesProvider::GetSheet(TEAM_B_PLAYER, kitFile);
    }

}

PlayerView::~PlayerView() {
    Logger::getInstance()->debug("DESTRUYENDO PLAYERVIEW");

    //TODO: delete clips in animation destructor
    for (unsigned int i = 0; i < animations.size(); i++) {
        delete (animations[i]);
    }
    delete previous_location;
}

void PlayerView::GetPlayerAngle()
{
    DIRECTION direction = this->player->GetDirection();
    switch(direction) {
        case DIRECTION::NORTH:
            angle = 0;
        break;
        case DIRECTION::WEST:
            angle = -90;
        break;
        case DIRECTION::SOUTH:
            angle = 180;
        break;
        case DIRECTION::EAST:
            angle = 90;
        break;
        case DIRECTION::NORTHEAST:
            angle = 45;
        break;
        case DIRECTION::NORTHWEST:
            angle = -45;
        break;
        case DIRECTION::SOUTHEAST:
            angle = 135;
        break;
        case DIRECTION::SOUTHWEST:
            angle = -135;
        break;
        default:
            angle = angle;
        break;
    }
}

void PlayerView::Render(int x_camera, int y_camera, int max_x, int max_y)
{
    this->GetPlayerAngle();
    int animation_index = current_animation_index;

    if (this->player->IsKicking()) {
        current_animation_index = KICKING_ANIMATION_INDEX;
    } else if (this->player->IsRecoveringBall()) {
        current_animation_index = RECOVERING_BALL_ANIMATION_INDEX;
    } else if(this->IsStill()) {
        current_animation_index = STILL_ANIMATION_INDEX;
    } else if(!this->IsStill()){
        current_animation_index = RUN_ANIMATION_INDEX;
    } else {
        current_animation_index = STILL_ANIMATION_INDEX;
    }
    if(animation_index != current_animation_index)
    {
        animations[current_animation_index]->Restart();
    }

    SDL_Rect* current_clip = animations[current_animation_index]->NextClip();
    int x, y;

    this->previous_location->UpdateX(player->GetLocation()->GetX());
    this->previous_location->UpdateY(player->GetLocation()->GetY());

    x = player->GetLocation()->GetX() - x_camera;
    y = player->GetLocation()->GetY() - y_camera;

    this->GetSelectorSheet();

    if (player->GetPlayerColor() != USER_COLOR::NO_COLOR) {
        selector_sheet->Render(x - (SELECTOR_SPRITE_WIDTH / 2), y - (SELECTOR_SPRITE_HEIGHT / 2), animations[SELECTOR_ANIMATION_INDEX]->NextClip(), 0);
    }

    sprite_sheet->Render( x - (SPRITE_WIDTH / 2), y - (SPRITE_HEIGHT / 2), current_clip, this->angle);
}

void PlayerView::GetSelectorSheet()
{
    if (this->player->GetPlayerColor() == USER_COLOR::RED)
    {
        this->selector_sheet = SpritesProvider::GetDefaultSheet(SELECTOR_A1);
    }
    else if (this->player->GetPlayerColor() == USER_COLOR::GREEN)
    {
        this->selector_sheet = SpritesProvider::GetDefaultSheet(SELECTOR_A2);
    }
    else if (this->player->GetPlayerColor() == USER_COLOR::YELLOW)
    {
        this->selector_sheet = SpritesProvider::GetDefaultSheet(SELECTOR_A3);
    }
    else if (this->player->GetPlayerColor() == USER_COLOR::BLUE)
    {
        this->selector_sheet = SpritesProvider::GetDefaultSheet(SELECTOR_A4);
    }
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
    Location* location = this->player->GetLocation();
    return location->GetX() == previous_location->GetX() &&
        location->GetY() == previous_location->GetY();
}
