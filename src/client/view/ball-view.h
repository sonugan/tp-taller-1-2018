#ifndef BALLVIEW_H
#define BALLVIEW_H

#include "../../shared/model/ball.h"
#include "abstract-view.h"
#include "sprites-provider.h"

class BallView : public AbstractView
{
    public:
        BallView(Ball* ball);
        virtual ~BallView();
        void Render(int x_camera, int y_camera, int max_x, int max_y);

    protected:

    private:
        Ball* ball;
};

#endif // BALLVIEW_H
