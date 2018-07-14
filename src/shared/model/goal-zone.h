#ifndef GOAL_ZONE_H
#define GOAL_ZONE_H

#include "ipitch-zone.h"

class Team;
class Ball;
class GoalZone : public iPitchZone
{
    public:
        GoalZone(Team* team, Location* top_left_corner, Location* bottom_right_corner);
        ~GoalZone();
        bool IsGoal(Ball* ball);
        void SetTeam(Team* team);
        Team* GetTeam();
        Location* GetTopLeftCorner();
    protected:
        Team* team;
    private:
};

#endif // GOAL_ZONE_H
