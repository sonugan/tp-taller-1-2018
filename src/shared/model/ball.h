#ifndef BALL_H
#define BALL_H

#include "location.h"
#include "trajectory.h"
#include <cstddef>

class Trajectory;
class Ball
{
    public:
        Ball();
        virtual ~Ball();
        Location* GetLocation();
        void UpdateLocation(int x, int y, int z);
        void SetTrajectory(Trajectory* new_trajectory);

    protected:

    private:
        Location* location;
        Trajectory* trajectory;
};

#endif // BALL_H
