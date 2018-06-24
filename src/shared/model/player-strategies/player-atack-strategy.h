#ifndef PLAYER_ATACK_ESTRATEGY_H
#define PLAYER_ATACK_ESTRATEGY_H

#include "iplayer-strategy.h"
#include "../player.h"
#include "../player-states/player-states.h"
#include "../../collision/circle.h"
#include "../../utils/coin-flipper.h"
#include <vector>
#include <cmath>
#include "../../logger.h"

class Player;
class PlayerAtackStrategy : public IPlayerStrategy
{
    public:
        PlayerAtackStrategy(Player* player);
        virtual ~PlayerAtackStrategy();
        void Play();
        bool IsRunningToArea(){ return is_running_to_area; };
    protected:
        Player* player;
    private:
        bool PassBall();
        bool IsNearGoalLine(Player* player);
        vector<Player*> GetEnemies();
        bool IsPlayerInFrontOfMe();
        bool ThereIsAnEnemyInFrontOfMe();
        bool IsTeamA();
        bool AreBetween(int a, int b, int value);
        vector<Player*> GetBuddies();
        bool RecoverInAtack();
        bool RunWithBall();
        bool RunToArea();
        bool Convoy();
        bool StayDefend();
        bool Kick();
        bool Cross();
        bool IsInGoalZone();
        bool IsInEnemyMiddle();
        bool IsOutisideShootingRange();
        bool IsExpectingACross(Player* player);
        bool IsBallInMyMiddle();
        bool IsRecovering();
        bool LongKick();
        bool MediumKick();
        bool IsKeeperInFrontOfMe(Keeper* keeper);
        Keeper* GetOpponetKeeper();
        void Point();
        bool BallIsFree();

        CoinFlipper* coin_flipper;
        static const int GOAL_POST_NORTH = 448;
        static const int GOAL_POST_SOUTH = 790;
        static const int MIDDLE = 960;
        static const int WIDTH = 20;
        static const int TEAM_A_GOAL_ZONE_X = 1422;
        static const int TEAM_B_GOAL_ZONE_X = 492;
        bool is_running_to_area = false;
        bool is_recovering = false;
};

#endif // PLAYER_ATACK_ESTRATEGY_H
