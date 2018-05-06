#ifndef MATCH_H
#define MATCH_H

#include "team.h"
#include "pitch.h"
#include "ball.h"

class Ball;
class Team;
class Match
{
    public:
        Match(Pitch* pitch, Team* team_a, Team* team_b, Ball* ball);
        virtual ~Match();
        Team* GetTeamA();
        Team* GetTeamB();
        Pitch* GetPitch();
        Ball* GetBall();

    private:
        Team* team_a;
        Team* team_b;
        Pitch* pitch;
        Ball* ball;
};

#endif // MATCH_H
