#include "player-view.h"
#include "logger.h"
#include <sys/stat.h>



bool File_Exists (const string& name)
{
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

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
    recover_sprite_2->x = 64;
    recover_sprite_2->y = 448;
    recover_sprite_2->w = this->width;
    recover_sprite_2->h = this->height;
    recover_ball_clips.push_back(recover_sprite_2);

    SDL_Rect* recover_sprite_3 = new SDL_Rect();
    recover_sprite_3->x = 128;
    recover_sprite_3->y = 448;
    recover_sprite_3->w = this->width;
    recover_sprite_3->h = this->height;
    recover_ball_clips.push_back(recover_sprite_3);

    SDL_Rect* recover_sprite_4 = new SDL_Rect();
    recover_sprite_4->x = 192;
    recover_sprite_3->y = 448;
    recover_sprite_4->w = this->width;
    recover_sprite_4->h = this->height;
    recover_ball_clips.push_back(recover_sprite_4);

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

    this->selector_sheet = new SpriteSheet(renderer, "seleccion3.png");

    Location* current_location = player->GetLocation();
    previous_location = new Location(current_location->GetX(), current_location->GetY(), current_location->GetZ());

    string kitFile = player->getTeam()->GetName();
    kitFile.append("/");
    kitFile.append(player->getTeam()->GetShirt());
    kitFile.append("-kit.png");

    if (File_Exists("src/sprites/" + kitFile)) {
            cout << "Cargando " << kitFile << endl;
        this->sprite_sheet = new SpriteSheet(renderer, kitFile);
    } else {
        Logger::getInstance()->error("No se encontro kit de camiseta en '" + kitFile + "'. Se procede a cargar la camiseta por defecto: 'team_a/home-kit.png'");
        //Por defecto cargo el home kit del team_a
        this->sprite_sheet = new SpriteSheet(renderer, "team_a/home-kit.png");
    }

}

PlayerView::~PlayerView() {
    Logger::getInstance()->debug("DESTRUYENDO PLAYERVIEW");
    delete sprite_sheet;
    delete selector_sheet;

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

void PlayerView::Render(int x_camera, int y_camera, int max_x, int max_y)
{
    this->GetPlayerAngle();
    if (IsKicking()) {
        current_animation_index = KICKING_ANIMATION_INDEX;

    } else if (IsRecoveringBall()) {
        current_animation_index = RECOVERING_BALL_ANIMATION_INDEX;

    } else if(IsStill()) {
        current_animation_index = STILL_ANIMATION_INDEX;

    } else {
        current_animation_index = RUN_ANIMATION_INDEX;
    }

    SDL_Rect* current_clip = animations[current_animation_index]->NextClip();
    int x, y;

    this->previous_location->UpdateX(player->GetLocation()->GetX());
    this->previous_location->UpdateY(player->GetLocation()->GetY());
    this->player->SetKicking(false);
    this->player->SetRecoveringBall(false);

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

        selector_sheet->Render(x, y, animations[SELECTOR_ANIMATION_INDEX]->NextClip(), 0);
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

bool PlayerView::IsKicking()
{
    return this->player->IsKicking();
}

bool PlayerView::IsRecoveringBall()
{
    return this->player->IsRecoveringBall();
}
