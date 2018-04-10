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
        void Render(int x_camera, int y_camera, int max_x, int max_y);
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
        Location* previous_location;
        bool IsStill();
        bool File_Exists(const string& name);
};

#endif // PLAYERVIEW_H
