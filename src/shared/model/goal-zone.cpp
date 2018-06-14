#include "goal-zone.h"

GoalZone::GoalZone(Location* top_left_corner, Location* bottom_right_corner, int height)
{
    this->top_left_corner = top_left_corner;
    this->bottom_right_corner = bottom_right_corner;
    this->zone_height = height;
}

GoalZone::~GoalZone()
{
    //dtor
}
