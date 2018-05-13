#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "../../shared/configuration/configuration.h"
#include "game/game-state.h"


class GameServer
{
    public:
        GameServer(Configuration* initial_configuration);
        virtual ~GameServer();

    protected:

    private:
        /* Attributes */
        GameState* game_state;

};

#endif // GAMESERVER_H
