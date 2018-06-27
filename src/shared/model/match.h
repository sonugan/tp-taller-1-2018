#ifndef MATCH_H
#define MATCH_H

#include "team.h"
#include "pitch.h"
#include "player.h"
#include "ball.h"
#include "../network/message-type.h"
#include "../utils/string-utils.h"
#include <string>
#include <map>
#include "team-number.h"

#include "match-time-type.h"
#include "match-state.h"
#include "timer.h"

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
        MATCH_TIME_TYPE GetMatchTime();
        void SetMatchTime(MATCH_TIME_TYPE match_time);
        MatchState* GetMatchState();
        void SetMatchState(MatchState* state);
        std::string GetRemainingTime();
        void SetRemainingTime(std::string remaining_time);
        Team* GetTeamByNumber(TEAM_NUMBER number);
        Team* GetOppositeTeam(Team* team);
        void SetKickOffLocations(TEAM_NUMBER kicker_team);
        void AddGoalToUser(std::string username, int goals);
        std::map<std::string, int> GetScoreBoard();
        void ResetUserGoals(std::string username);
        void ChangeTeamSides();
    private:
        Team* team_a;
        Team* team_b;
        Pitch* pitch;
        Ball* ball;
        MATCH_TIME_TYPE match_time;
        MatchState* match_state;
        std::string remaining_time;

        std::map<std::string, int> scores; // username - score

        int SafeStoi(const std::string& str);
};

#endif // MATCH_H
