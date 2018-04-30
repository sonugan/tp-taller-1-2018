#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "player.h"
#include "match.h"
#include "formation.h"
#include <string>

using namespace std;

class Match;
class Player; //  forward declaration
class Team
{
    public:
        Team(Formation* formation, string name, string shirt);
        virtual ~Team();
        std::vector<Player*> GetPlayers();
        void SetFormation(Formation* formation);
        void SetMatch(Match* match);
        Formation* GetFormation();
        Match* GetMatch();
        void AddPlayer(Player* player);
        static const unsigned int TEAM_SIZE = 7;
        string GetName();
        string GetShirt();
        Player* GetSelectedPlayer();
    private:
        std::vector<Player*> players;
        Formation* formation;
        string name;
        string shirt;
        Match* match;
};

#endif // TEAM_H
