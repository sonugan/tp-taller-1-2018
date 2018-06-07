#ifndef MATCH_H
#define MATCH_H

#include "team.h"
#include "pitch.h"
#include "ball.h"
#include "player.h"
#include "timer.h"
#include "../network/message-type.h"
#include "../utils/string-utils.h"
#include <string>

class Ball;
class Team;

class Match
{
    public:
        Match(Pitch* pitch, Team* team_a, Team* team_b, Ball* ball, Timer* timer);
        virtual ~Match();
        Team* GetTeamA();
        Team* GetTeamB();
        Pitch* GetPitch();
        Ball* GetBall();
        Timer* GetTimer();
        std::string Serialize();
        void DeserializeAndUpdate(std::string serialized);
        void StartTimer();

    private:
        Team* team_a;
        Team* team_b;
        Pitch* pitch;
        Ball* ball;
        Timer* timer;

        int SafeStoi(const std::string& str);
};

#endif // MATCH_H
