#ifndef GOAL_ZONE_H
#define GOAL_ZONE_H

#include "ipitch-zone.h"

class GoalZone : public iPitchZone
{
    public:
        GoalZone(Location* top_left_corner, Location* bottom_right_corner, int height);
        ~GoalZone();
    protected:

    private:
};

#endif // GOAL_ZONE_H
