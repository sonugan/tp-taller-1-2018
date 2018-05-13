#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "../../shared/configuration/configuration.h"
#include "game/game-state.h"


class GameServer
{
    public:
        GameServer(Configuration* initial_configuration);
        virtual ~GameServer();

        void Start();
        void Stop();


    protected:

    private:
        /* Attributes */
        GameState* game_state;
        bool is_running = false;

};

#endif // GAMESERVER_H
