#ifndef BALLVIEW_H
#define BALLVIEW_H

#include "../../shared/model/ball.h"
#include "abstract-view.h"
#include "sprites-provider.h"
#include "ishowable.h"

class BallView : public AbstractView, public IShowable
{
    public:
        BallView(Ball* ball);
        virtual ~BallView();
        void Render(int x_camera, int y_camera, int max_x, int max_y);
        Location* GetLocation();
        Location* GetPreviousLocation();
        bool IsStill();
        bool GoingUp();
        bool GoingDown();

    protected:

    private:
        static const int SPRITE_WIDTH = 20;
        static const int SPRITE_HEIGHT = 20;
        Ball* ball;
        Location* previous_location;
};

#endif // BALLVIEW_H
