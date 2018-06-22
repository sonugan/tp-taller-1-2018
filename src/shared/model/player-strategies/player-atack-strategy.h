#ifndef PLAYER_ATACK_ESTRATEGY_H
#define PLAYER_ATACK_ESTRATEGY_H

#include "iplayer-strategy.h"
#include "../player.h"
#include "player-states.h"
#include "../../collision/circle.h"
#include "../../utils/coin-flipper.h"
#include <vector>
#include <cmath>

class Player;
class PlayerAtackStrategy : public IPlayerStrategy
{
    public:
        PlayerAtackStrategy(Player* player);
        virtual ~PlayerAtackStrategy();
        void Play();
    protected:
        Player* player;
    private:
        bool PassBall();
        bool IsNearGoalLine(Player* player);
        vector<Player*> GetEnemies();
        bool IsPlayerInFrontOfMe();
        bool IsTeamA();
        bool AreBetween(int a, int b, int value);
        vector<Player*> GetBuddies();
        Circle* vision_area;
        CoinFlipper* coin_flipper;
};

#endif // PLAYER_ATACK_ESTRATEGY_H
