#ifndef GOALPOST_H
#define GOALPOST_H

#include "ipitch-zone.h"

class Team;
class Ball;
class GoalPost : public iPitchZone
{
    public:
        GoalPost(Location* top_left_corner, Location* bottom_right_corner);
        ~GoalPost();
        bool IsTouching(Ball* ball);

    protected:
    private:
};

#endif // GOALPOST_H
