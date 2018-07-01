#include "goalpost.h"
#include "location.h"
#include "ball.h"

GoalPost::GoalPost(Location* top_left_corner, Location* bottom_right_corner)
{
    this->top_left_corner = top_left_corner;
    this->bottom_right_corner = bottom_right_corner;
}

GoalPost::~GoalPost()
{
    //dtor
}

bool GoalPost::IsTouching(Ball* ball)
{
    //Location* ball_top_left_corner = new Location(ball->GetLocation()->GetX() - Ball::BALL_TRIDIMENSIONAL_OFFSET, ball->GetLocation()->GetY() - Ball::BALL_TRIDIMENSIONAL_OFFSET, ball->GetLocation()->GetZ() - Ball::BALL_TRIDIMENSIONAL_OFFSET);
    //Location* ball_bottom_right_corner = new Location(ball->GetLocation()->GetX() + Ball::BALL_TRIDIMENSIONAL_OFFSET, ball->GetLocation()->GetY() + Ball::BALL_TRIDIMENSIONAL_OFFSET, ball->GetLocation()->GetZ() + Ball::BALL_TRIDIMENSIONAL_OFFSET);

    int ball_top_left_corner_x = ball->GetLocation()->GetX() - Ball::BALL_TRIDIMENSIONAL_OFFSET;
    int ball_top_left_corner_y = ball->GetLocation()->GetY() - Ball::BALL_TRIDIMENSIONAL_OFFSET;
    int ball_top_left_corner_z = ball->GetLocation()->GetZ() - Ball::BALL_TRIDIMENSIONAL_OFFSET;

    int ball_bottom_right_corner_x = ball->GetLocation()->GetX() + Ball::BALL_TRIDIMENSIONAL_OFFSET;
    int ball_bottom_right_corner_y = ball->GetLocation()->GetY() + Ball::BALL_TRIDIMENSIONAL_OFFSET;
    int ball_bottom_right_corner_z = ball->GetLocation()->GetZ() + Ball::BALL_TRIDIMENSIONAL_OFFSET;

    return  ((this->top_left_corner->GetX() <= ball_bottom_right_corner_x) && (this->bottom_right_corner->GetX() >= ball_top_left_corner_x)) &&
            ((this->top_left_corner->GetY() <= ball_bottom_right_corner_y) && (this->bottom_right_corner->GetY() >= ball_top_left_corner_y)) &&
            ((this->top_left_corner->GetZ() <= ball_bottom_right_corner_z) && (this->bottom_right_corner->GetZ() >= ball_top_left_corner_z));
}
