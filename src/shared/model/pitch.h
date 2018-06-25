#ifndef PITCH_H
#define PITCH_H

#include "goal-zone.h"
#include "throw-in-zone.h"
#include "end-line-zone.h"
#include "goalpost.h"

class Team;
class Ball;
class Pitch
{
    public:
        Pitch(Team* team_a, Team* team_b);
        virtual ~Pitch();
        Team* ScoringAtSomeGoal(Ball* ball);
        bool BallTouchingThrowIn(Ball* ball);
        Team* BallTouchingEndLineZone(Ball* ball);
        bool BallTouchingGoalPost(Ball* ball);
        void ChangeTeamSides(Team* team_a, Team* team_b);
    protected:
        GoalZone* east_goal;
        GoalZone* west_goal;
        ThrowInZone* throw_in_zones[2];
        EndLineZone* end_line_zones[6];
        GoalPost* goal_posts[6];
        bool IsGoalOnEastGoal(Ball* ball);
        bool IsGoalOnWestGoal(Ball* ball);
    private:
};

#endif // PITCH_H
