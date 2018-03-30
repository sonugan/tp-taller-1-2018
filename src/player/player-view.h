#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "player.h"
#include "../common/abstract-view.h"
#include "../common/ishowable.h"
#include "../camera/camera.h"

class PlayerView : public AbstractView, public IShowable
{
    public:
        PlayerView(Player* player, SDL_Renderer* renderer);
        virtual ~PlayerView();
        void Render();
        void Render(int xCamera, int yCamera, int maxX, int maxY);
        Location* GetLocation();
    protected:

    private:
        Player* player;
        int frame;
        static constexpr float FRAMES_PER_EVENT = 0.3;
        static const int WALKING_ANIMATION_FRAMES = 4;
        double angle = 0;

};

#endif // PLAYERVIEW_H
