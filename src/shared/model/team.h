#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "player.h"
#include "match.h"
#include "keeper.h"
#include "formation.h"
#include "../configuration/configuration.h"
#include <string>

using namespace std;

class Keeper; //  forward declaration
class Match; //  forward declaration
class Player; //  forward declaration
class Configuration; //  forward declaration

class Team
{
    public:
        Team(Formation* formation, string name, string shirt, TEAM_NUMBER team_number);
        virtual ~Team();
        std::vector<Player*> GetPlayers();
        std::vector<Player*> GetAvailablePlayers();
        std::vector<Player*> GetSelectedPlayers();
        Player* GetPlayerByPositionIndex(unsigned int position_index);
        void SetKeeper(Keeper* keeper);
        Keeper* GetKeeper();
        void SetFormation(Formation* formation);
        void SetMatch(Match* match);
        Formation* GetFormation();
        Match* GetMatch();
        TEAM_NUMBER GetTeamNumber();
        void AddPlayer(Player* player);
        int SetGoals(int goals);
        Location* GetTeamAGoalLine();
        Location* GetTeamBGoalLine();
        bool HasBall();
	static const unsigned int TEAM_SIZE = 6;
        string GetName();
        string GetShirt();
        void SetShirt(string shirt);
        void UpdateFormation();
        void AddGoal();
        int GetGoals();
        //USAR SOLO DESDE EL CLIENTE
        Player* GetSelectedPlayer();
    private:
        std::vector<Player*> players;
        Keeper* keeper;
        Formation* formation;
        string name;
        string shirt;
        Match* match;
        int goals;
        TEAM_NUMBER team_number;
        Location* team_a_goal_line;
        Location* team_b_goal_line;
};

#endif // TEAM_H
