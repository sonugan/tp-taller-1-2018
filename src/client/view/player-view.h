#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "../../shared/model/player.h"
#include "abstract-view.h"
#include "ishowable.h"
#include "sprites-provider.h"
#include "camera.h"

class PlayerView : public AbstractView, public IShowable
{
    public:
        PlayerView(Player* player);
        virtual ~PlayerView();
        void Render(int x_camera, int y_camera, int max_x, int max_y);
        Location* GetLocation();
        static constexpr float FRAMES_PER_EVENT = 0.3;
        static constexpr int RUN_FRAME_COUNT = 4;
        static constexpr int KICKING_FRAME_COUNT = 4;
        static constexpr int RECOVERING_FRAME_COUNT = 7;
    protected:
        void SetAnimation(Animation* animation);
    private:
        Player* player;
        int frame;
        static constexpr int RUN_ANIMATION_INDEX = 0;
        static constexpr int STILL_ANIMATION_INDEX = 1;
        static constexpr int KICKING_ANIMATION_INDEX = 2;
        static constexpr int RECOVERING_BALL_ANIMATION_INDEX = 3;
        static constexpr int SELECTOR_ANIMATION_INDEX = 4;
        static const int SPRITE_WIDTH = 64;
        static const int SPRITE_HEIGHT = 64;
        static const int SELECTOR_SPRITE_WIDTH = 64;
        static const int SELECTOR_SPRITE_HEIGHT = 64;
        double angle = 0;
        Location* previous_location;
        void GetPlayerAngle();
        SpriteSheet* selector_sheet;
        void GetSelectorSheet();
        bool IsStill();
};

#endif // PLAYERVIEW_H
