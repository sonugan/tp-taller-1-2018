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

#include "match-time-type.h"
#include "match-state.h"

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
        Timer* GetTimer();
        std::string Serialize();
        void DeserializeAndUpdate(std::string serialized);
        void SetMatchTime(MATCH_TIME_TYPE match_time);
        void SetMatchState(MatchState* state);
        std::string GetRemainingTime();
        void SetRemainingTime(std::string remaining_time);

    private:
        Team* team_a;
        Team* team_b;
        Pitch* pitch;
        Ball* ball;
        MATCH_TIME_TYPE match_time;
        MatchState* match_state;
        std::string remaining_time;

        int SafeStoi(const std::string& str);
};

#endif // MATCH_H
