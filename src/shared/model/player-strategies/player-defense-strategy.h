#ifndef PLAYER_DEFENSE_ESTRATEGY_H
#define PLAYER_DEFENSE_ESTRATEGY_H

#include "iplayer-strategy.h"
#include "../player.h"
#include "player-states.h"
#include "../../collision/rectangle.h"
#include "../../utils/coin-flipper.h"

using namespace std;

class Player;
class PlayerDefenseStrategy : public IPlayerStrategy
{
    public:
        PlayerDefenseStrategy(Player* player);
        virtual ~PlayerDefenseStrategy();
        void Play();
        void SetDefenseArea(Rectangle* rectangle);
        bool IsRunningToArea() { return false; };
    protected:
        Player* player;
    private:
        bool KickBall();
        Rectangle* rectangle;
        CoinFlipper* coin_flipper;
};

#endif // PLAYER_DEFENSE_ESTRATEGY_H
