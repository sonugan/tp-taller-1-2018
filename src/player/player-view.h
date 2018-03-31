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
        void Render(int xCamera, int yCamera, int maxX, int maxY);
        Location* GetLocation();
    protected:
        void SetAnimation(Animation* animation);
    private:
        Player* player;
        int frame;
        static constexpr float FRAMES_PER_EVENT = 0.3;
        static constexpr int RUN_ANIMATION_INDEX = 0;
        static constexpr int STILL_ANIMATION_INDEX = 1;
        double angle = 0;
        Location* previousLocation;
        bool IsStill();
};

#endif // PLAYERVIEW_H
