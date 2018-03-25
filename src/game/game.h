#ifndef GAME_H
#define GAME_H

#include "../pitch/pitch.h"
#include "../pitch/pitch-view.h"
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
        PitchView* pitch_view;
        Player* player;

        void CreateModel();
        void CreateViews();
        void DestroyModel();
        void DestroyViews();
};

#endif // GAME_H
