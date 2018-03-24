#ifndef GAME_H
#define GAME_H

#include "../pitch/pitch.h"
#include "../player/player.h"


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

        void createModel();
        void createViews();
};

#endif // GAME_H
