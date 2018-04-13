#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "../player/player.h"
#include "formation.h"
#include <string>

using namespace std;

class Player; //  forward declaration
class Team
{
    public:
        Team(Formation* formation, string name, string shirt);
        virtual ~Team();
        std::vector<Player*> GetPlayers();
        void SetFormation(Formation* formation);
        Formation* GetFormation();
        void AddPlayer(Player* player);
        static const unsigned int TEAM_SIZE = 7;
        string GetName();
        string GetShirt();
    private:
        std::vector<Player*> players;
        Formation* formation;
        string name;
        string shirt;
};

#endif // TEAM_H
