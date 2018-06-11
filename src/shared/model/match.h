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
#include "match-state.h"
#include "match-time-type.h"

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
        void SetMatchTime(MATCH_TIME_TYPE match_time);
        void SetMatchState(MATCH_STATE state);

    private:
        Team* team_a;
        Team* team_b;
        Pitch* pitch;
        Ball* ball;
        Timer* timer;
        MATCH_TIME_TYPE match_time;
        MATCH_STATE match_state;

        int SafeStoi(const std::string& str);
};

#endif // MATCH_H
