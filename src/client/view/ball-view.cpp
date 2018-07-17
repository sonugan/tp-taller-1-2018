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

    std::vector<SDL_Rect*> upwards_ball_clips1;
    SDL_Rect* sprite6 = new SDL_Rect();
    sprite6->x = 340;
    sprite6->y = 167;
    sprite6->w = 20;
    sprite6->h = 20;

    std::vector<SDL_Rect*> upwards_ball_clips2;
    SDL_Rect* sprite7 = new SDL_Rect();
    sprite7->x = 378;
    sprite7->y = 168;
    sprite7->w = 22;
    sprite7->h = 22;

    std::vector<SDL_Rect*> upwards_ball_clips3;
    SDL_Rect* sprite8 = new SDL_Rect();
    sprite8->x = 415;
    sprite8->y = 168;
    sprite8->w = 23;
    sprite8->h = 23;

    std::vector<SDL_Rect*> upwards_ball_clips4;
    SDL_Rect* sprite9 = new SDL_Rect();
    sprite9->x = 458;
    sprite9->y = 165;
    sprite9->w = 25;
    sprite9->h = 25;

    std::vector<SDL_Rect*> upwards_ball_clips5;
    SDL_Rect* sprite10 = new SDL_Rect();
    sprite10->x = 498;
    sprite10->y = 165;
    sprite10->w = 27;
    sprite10->h = 27;

    std::vector<SDL_Rect*> upwards_ball_clips6;
    SDL_Rect* sprite11 = new SDL_Rect();
    sprite11->x = 538;
    sprite11->y = 163;
    sprite11->w = 29;
    sprite11->h = 29;

    std::vector<SDL_Rect*> upwards_ball_clips7;
    SDL_Rect* sprite12 = new SDL_Rect();
    sprite12->x = 574;
    sprite12->y = 161;
    sprite12->w = 32;
    sprite12->h = 32;

    std::vector<SDL_Rect*> upwards_ball_clips8;
    SDL_Rect* sprite13 = new SDL_Rect();
    sprite13->x = 612;
    sprite13->y = 160;
    sprite13->w = 34;
    sprite13->h = 34;

    std::vector<SDL_Rect*> upwards_ball_clips9;
//    SDL_Rect* sprite14 = new SDL_Rect();
//    sprite14->x = 654;
//    sprite14->y = 158;
//    sprite14->w = 36;
//    sprite14->h = 36;
    
    SDL_Rect* sprite15 = new SDL_Rect();
    sprite15->x = 0;
    sprite15->y = 84;
    sprite15->w = 41;
    sprite15->h = 42;
    
    SDL_Rect* sprite16 = new SDL_Rect();
    sprite16->x = 42;
    sprite16->y = 84;
    sprite16->w = 41;
    sprite16->h = 42;
    
    SDL_Rect* sprite17 = new SDL_Rect();
    sprite17->x = 83;
    sprite17->y = 84;
    sprite17->w = 41;
    sprite17->h = 42;
    
    SDL_Rect* sprite18 = new SDL_Rect();
    sprite18->x = 124;
    sprite18->y = 84;
    sprite18->w = 41;
    sprite18->h = 42;
//    upwards_ball_clips9.push_back(sprite14);
    upwards_ball_clips9.push_back(sprite15);
    upwards_ball_clips9.push_back(sprite16);
    upwards_ball_clips9.push_back(sprite17);
    upwards_ball_clips9.push_back(sprite18);

    upwards_ball_clips1.push_back(sprite6);
    upwards_ball_clips2.push_back(sprite7);
    upwards_ball_clips3.push_back(sprite8);
    upwards_ball_clips4.push_back(sprite9);
    upwards_ball_clips5.push_back(sprite10);
    upwards_ball_clips6.push_back(sprite11);
    upwards_ball_clips7.push_back(sprite12);
    upwards_ball_clips8.push_back(sprite13);


    animations.push_back(new Animation("upwards_ball1", upwards_ball_clips1, 1));
    animations.push_back(new Animation("upwards_ball2", upwards_ball_clips2, 1));
    animations.push_back(new Animation("upwards_ball3", upwards_ball_clips3, 1));
    animations.push_back(new Animation("upwards_ball4", upwards_ball_clips4, 1));
    animations.push_back(new Animation("upwards_ball5", upwards_ball_clips5, 1));
    animations.push_back(new Animation("upwards_ball6", upwards_ball_clips6, 1));
    animations.push_back(new Animation("upwards_ball7", upwards_ball_clips7, 1));
    animations.push_back(new Animation("upwards_ball8", upwards_ball_clips8, 1));
    animations.push_back(new Animation("upwards_ball9", upwards_ball_clips9, 0.2));

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

    int ball_z = ball->GetLocation()->GetZ();


    if ((ball_z > 0) && (ball_z < 20)) {
        current_animation_index = 2;
    }else if ((ball_z >= 20) && (ball_z < 40)){
        current_animation_index = 3;
    } else if ((ball_z >= 40) && (ball_z < 80)) {
        current_animation_index = 4;
    }else if ((ball_z >= 80) && (ball_z < 110)){
        current_animation_index = 5;
    } else if ((ball_z >= 110) && (ball_z < 150)) {
        current_animation_index = 6;
    }else if ((ball_z >= 150) && (ball_z < 180)){
        current_animation_index = 7;
    }else if ((ball_z >= 180) && (ball_z < 210)){
        current_animation_index = 8;
    }else if ((ball_z >= 210) && (ball_z < 240)){
        current_animation_index = 9;
    }else if (ball_z >= 240){
        current_animation_index = 10;
    }else if(IsStill()) {
        current_animation_index = 1;
        Logger::getInstance()->info("BALL IS STILL");
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
