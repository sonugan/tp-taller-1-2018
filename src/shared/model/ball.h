#ifndef BALL_H
#define BALL_H

#include "location.h"

class Ball
{
    public:
        Ball();
        virtual ~Ball();
        Location* GetLocation();
        void UpdateLocation(int x, int y, int z);

    protected:

    private:
        Location* location;
};

#endif // BALL_H
