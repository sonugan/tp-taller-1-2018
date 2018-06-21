#include "ball-view.h"

BallView::BallView(Ball* ball)
{
    this->width = 31;
    this->height = 31;
    this->ball = ball;

    SDL_Rect* sprite1 = new SDL_Rect();
    sprite1->x = 13;
    sprite1->y = 13;
    sprite1->w = 20;
    sprite1->h = 20;

    SDL_Rect* sprite2 = new SDL_Rect();
    sprite2->x = 53;
    sprite2->y = 13;
    sprite2->w = 20;
    sprite2->h = 20;

    SDL_Rect* sprite3 = new SDL_Rect();
    sprite3->x = 94;
    sprite3->y = 13;
    sprite3->w = 20;
    sprite3->h = 20;

    SDL_Rect* sprite4 = new SDL_Rect();
    sprite4->x = 135;
    sprite4->y = 13;
    sprite4->w = 20;
    sprite4->h = 20;

    std::vector<SDL_Rect*> ball_clips;
    ball_clips.push_back(sprite1);
    ball_clips.push_back(sprite2);
    ball_clips.push_back(sprite3);
    ball_clips.push_back(sprite4);

    animations.push_back(new Animation("ball", ball_clips, 0.7));

    std::vector<SDL_Rect*> ball_still_clips;
    SDL_Rect* sprite5 = new SDL_Rect();
    sprite5->x = 13;
    sprite5->y = 13;
    sprite5->w = 20;
    sprite5->h = 20;

    ball_still_clips.push_back(sprite5);

    animations.push_back(new Animation("ball_still", ball_still_clips, 0.3));

    std::vector<SDL_Rect*> upwards_ball_clips;
    SDL_Rect* sprite6 = new SDL_Rect();
    sprite6->x = 340;
    sprite6->y = 167;
    sprite6->w = 20;
    sprite6->h = 20;

    SDL_Rect* sprite7 = new SDL_Rect();
    sprite7->x = 378;
    sprite7->y = 168;
    sprite7->w = 22;
    sprite7->h = 22;

    SDL_Rect* sprite8 = new SDL_Rect();
    sprite8->x = 458;
    sprite8->y = 165;
    sprite8->w = 25;
    sprite8->h = 25;

    SDL_Rect* sprite9 = new SDL_Rect();
    sprite9->x = 538;
    sprite9->y = 163;
    sprite9->w = 27;
    sprite9->h = 27;

    SDL_Rect* sprite10 = new SDL_Rect();
    sprite10->x = 573;
    sprite10->y = 160;
    sprite10->w = 30;
    sprite10->h = 30;

    SDL_Rect* sprite11 = new SDL_Rect();
    sprite11->x = 655;
    sprite11->y = 158;
    sprite11->w = 32;
    sprite11->h = 32;

    upwards_ball_clips.push_back(sprite6);
    upwards_ball_clips.push_back(sprite7);
    upwards_ball_clips.push_back(sprite8);
    upwards_ball_clips.push_back(sprite9);
    upwards_ball_clips.push_back(sprite10);
    upwards_ball_clips.push_back(sprite11);

    animations.push_back(new Animation("upwards_ball", upwards_ball_clips, 0.3));

    std::vector<SDL_Rect*> downwards_ball_clips;

    SDL_Rect* sprite12 = new SDL_Rect();
    sprite12->x = 655;
    sprite12->y = 158;
    sprite12->w = 32;
    sprite12->h = 32;

    SDL_Rect* sprite13 = new SDL_Rect();
    sprite13->x = 573;
    sprite13->y = 160;
    sprite13->w = 30;
    sprite13->h = 30;

    SDL_Rect* sprite14 = new SDL_Rect();
    sprite14->x = 538;
    sprite14->y = 163;
    sprite14->w = 27;
    sprite14->h = 27;

    SDL_Rect* sprite15 = new SDL_Rect();
    sprite15->x = 458;
    sprite15->y = 165;
    sprite15->w = 25;
    sprite15->h = 25;

    SDL_Rect* sprite16 = new SDL_Rect();
    sprite16->x = 378;
    sprite16->y = 168;
    sprite16->w = 22;
    sprite16->h = 22;

    SDL_Rect* sprite17 = new SDL_Rect();
    sprite17->x = 340;
    sprite17->y = 167;
    sprite17->w = 20;
    sprite17->h = 20;

    downwards_ball_clips.push_back(sprite12);
    downwards_ball_clips.push_back(sprite13);
    downwards_ball_clips.push_back(sprite14);
    downwards_ball_clips.push_back(sprite15);
    downwards_ball_clips.push_back(sprite16);
    downwards_ball_clips.push_back(sprite17);

    animations.push_back(new Animation("downwards_ball", downwards_ball_clips, 0.3));

    current_animation_index = 0;

    Location* current_location = this->GetLocation();
    previous_location = new Location(current_location->GetX(), current_location->GetY(), current_location->GetZ());

	this->sprite_sheet = SpritesProvider::GetDefaultSheet(BALL);
}

BallView::~BallView()
{
	Logger::getInstance()->debug("DESTRUYENDO BALLVIEW");

    //TODO: delete clips in animation destructor
    for (unsigned int i = 0; i < animations.size(); i++) {
        delete (animations[i]);
    }
    delete previous_location;
}

void BallView::Render(int x_camera, int y_camera, int max_x, int max_y) {

    if(IsStill()) {
        current_animation_index = 1;
        Logger::getInstance()->info("BALL IS STILL");
    } else if (this->GoingUp()) {
        current_animation_index = 2;
    }else if (this->GoingDown()) {
        current_animation_index = 3;
    }else{
        current_animation_index = 0;
    }

    SDL_Rect* current_clip = this->animations[current_animation_index]->NextClip();

    int x, y;

    this->previous_location->UpdateX(ball->GetLocation()->GetX());
    this->previous_location->UpdateY(ball->GetLocation()->GetY());
    this->previous_location->UpdateZ(ball->GetLocation()->GetZ());

    x = ball->GetLocation()->GetX() - (Ball::BALL_TRIDIMENSIONAL_OFFSET * 2) - x_camera;
    y = ball->GetLocation()->GetY() - (Ball::BALL_TRIDIMENSIONAL_OFFSET * 2)- y_camera;

    sprite_sheet->Render( x, y, current_clip );
}

Location* BallView::GetLocation() {
    return this->ball->GetLocation();
}

Location* BallView::GetPreviousLocation() {
    return this->ball->GetPreviousLocation();
}

bool BallView::IsStill()
{
    Location* current_location = this->GetLocation();
    bool still = (current_location->GetX() == previous_location->GetX() && current_location->GetY() == previous_location->GetY());
    return still;
}

bool BallView::GoingUp()
{
    TRAJECTORY_TYPE trajectory_type = ball->GetTrajectory()->GetTrajectoryType();
    return trajectory_type == TRAJECTORY_TYPE::UPWARDS;
}

bool BallView::GoingDown()
{
    TRAJECTORY_TYPE trajectory_type = ball->GetTrajectory()->GetTrajectoryType();
    return trajectory_type == TRAJECTORY_TYPE::DOWNWARDS;
}
