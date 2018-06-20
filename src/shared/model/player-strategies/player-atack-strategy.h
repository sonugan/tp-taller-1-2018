#ifndef PLAYER_ATACK_ESTRATEGY_H
#define PLAYER_ATACK_ESTRATEGY_H

#include "iplayer-strategy.h"
#include "../player.h"
#include "player-states.h"

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
};

#endif // PLAYER_ATACK_ESTRATEGY_H
