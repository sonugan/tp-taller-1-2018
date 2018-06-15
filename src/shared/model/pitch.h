#ifndef PITCH_H
#define PITCH_H

#include "goal-zone.h"

class Team;
class Ball;
class Pitch
{
    public:
        Pitch(Team* team_a, Team* team_b);
        virtual ~Pitch();
        Team* ScoringAtSomeGoal(Ball* ball);
    protected:
        GoalZone* east_goal;
        GoalZone* west_goal;
        bool IsGoalOnEastGoal(Ball* ball);
        bool IsGoalOnWestGoal(Ball* ball);
    private:
};

#endif // PITCH_H
