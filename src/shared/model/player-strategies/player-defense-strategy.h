#ifndef PLAYER_DEFENSE_ESTRATEGY_H
#define PLAYER_DEFENSE_ESTRATEGY_H

#include "iplayer-strategy.h"
#include "../player.h"
#include "player-states.h"
#include "../../collision/rectangle.h"

using namespace std;

class Player;
class PlayerDefenseStrategy : public IPlayerStrategy
{
    public:
        PlayerDefenseStrategy(Player* player);
        virtual ~PlayerDefenseStrategy();
        void Play();
        void SetDefenseArea(Rectangle* rectangle);
    protected:
        Player* player;
    private:
        Rectangle* rectangle;
};

#endif // PLAYER_DEFENSE_ESTRATEGY_H
