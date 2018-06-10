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
    } else {
        current_animation_index = 0;
    }

    SDL_Rect* current_clip = this->animations[current_animation_index]->NextClip();

    int x, y;

    this->previous_location->UpdateX(ball->GetLocation()->GetX());
    this->previous_location->UpdateY(ball->GetLocation()->GetY());

    x = ball->GetLocation()->GetX() - (Ball::BALL_TRIDIMENSIONAL_OFFSET / 2) - x_camera;
    y = ball->GetLocation()->GetY() - (Ball::BALL_TRIDIMENSIONAL_OFFSET / 2)- y_camera;

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
    bool still = current_location->GetX() == previous_location->GetX()
        && current_location->GetY() == previous_location->GetY();
    return still;
}
