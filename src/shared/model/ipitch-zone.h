#ifndef IPITCH_ZONE_H
#define IPITCH_ZONE_H

#include "location.h"

class Ball;
class iPitchZone
{
    public:
        iPitchZone() {};
        virtual ~iPitchZone() {};
    protected:
        Location* top_left_corner;
        Location* bottom_right_corner;
        /*bool IsBallInZone(Ball* ball)
        {
            Location* ball_top_left_corner = new Location(ball->GetLocation()->GetX() - Ball::BALL_TRIDIMENSIONAL_OFFSET, ball->GetLocation()->GetY() - Ball::BALL_TRIDIMENSIONAL_OFFSET, ball->GetLocation()->GetZ() - Ball::BALL_TRIDIMENSIONAL_OFFSET);
            Location* ball_bottom_right_corner = new Location(ball->GetLocation()->GetX() + Ball::BALL_TRIDIMENSIONAL_OFFSET, ball->GetLocation()->GetY() + Ball::BALL_TRIDIMENSIONAL_OFFSET, ball->GetLocation()->GetZ() + Ball::BALL_TRIDIMENSIONAL_OFFSET);

            return  ((this->top_left_corner->GetX() <= ball_bottom_right_corner->GetX()) && (this->bottom_right_corner->GetX() >= ball_top_left_corner->GetX()) &&
                    ((this->top_left_corner->GetY() <= ball_bottom_right_corner->GetY()) && (this->bottom_right_corner->GetY() >= ball_top_left_corner->GetY())) &&
                    ((this->top_left_corner->GetZ() <= ball_bottom_right_corner->GetZ()) && (this->bottom_right_corner->GetZ() >= ball_top_left_corner->GetZ())));
                    return true;
        }*/
    private:
};

#endif // IPITCH_ZONE_H
