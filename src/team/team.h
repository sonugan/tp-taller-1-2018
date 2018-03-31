#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "../player/player.h"
#include "formation.h"

class Player; //  forward declaration
class Team
{
    public:
        Team(Formation* formation);
        virtual ~Team();
        std::vector<Player*> GetPlayers();
        void SetFormation(Formation* formation);
        Formation* GetFormation();
        Formation* SetFormation();

        void AddPlayer(Player* player);
        static const unsigned int TEAM_SIZE = 7;

    private:
        std::vector<Player*> players;
        Formation* formation;
};

#endif // TEAM_H
