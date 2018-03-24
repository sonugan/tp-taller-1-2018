#ifndef GAME_H
#define GAME_H

#include "pitch.h"
#include "player.h"


class Game
{
    public:
        Game();
        virtual ~Game();
        void Start();
        void End();

    protected:

    private:

        Pitch* pitch;
        Player* player;
};

#endif // GAME_H
