#ifndef MATCH_H
#define MATCH_H

#include "team.h"
#include "pitch.h"
#include "player.h"
#include "ball.h"
#include "../network/message-type.h"
#include "../utils/string-utils.h"
#include <string>
#include "team-number.h"

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
        std::string Serialize();
        void DeserializeAndUpdate(std::string serialized);
        Team* GetTeamByNumber(TEAM_NUMBER number);
        Team* GetOppositeTeam(Team* team);
    private:
        Team* team_a;
        Team* team_b;
        Pitch* pitch;
        Ball* ball;

        int SafeStoi(const std::string& str);
};

#endif // MATCH_H
