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
        bool Kick();
        bool Cross();
        bool IsInGoalZone();
        bool IsInEnemyMiddle();
        bool IsOutisideShootingRange();
        bool IsExpectingACross(Player* player);
        bool LongKick();
        bool MediumKick();
        bool IsKeeperInFrontOfMe(Keeper* keeper);
        Keeper* GetOpponetKeeper();
        void Point();
        Circle* vision_area;
        CoinFlipper* coin_flipper;

        static const int GOAL_POST_NORTH = 448;
        static const int GOAL_POST_SOUTH = 790;
        static const int MIDDLE = 960;
        static const int WIDTH = 20;
};

#endif // PLAYER_ATACK_ESTRATEGY_H
