#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "player.h"
#include "../common/abstract-view.h"

class PlayerView : public AbstractView
{
    public:
        PlayerView(Player* player, SDL_Renderer* renderer);
        virtual ~PlayerView();
        void Render();

    protected:

    private:
        Player* player;
        int frame;
        static constexpr float FRAMES_PER_EVENT = 0.3;
        static const int WALKING_ANIMATION_FRAMES = 4;
};

#endif // PLAYERVIEW_H
