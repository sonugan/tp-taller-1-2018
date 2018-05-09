#ifndef BALL_H
#define BALL_H

#include "location.h"
#include "player.h"
#include "trajectory.h"
#include <cstddef>

class Trajectory;
class Player;
class Ball
{
    public:
        Ball();
        virtual ~Ball();
        Location* GetLocation();
        Location* GetPreviousLocation();
        void SetTrajectory(Trajectory* new_trajectory);
        void Move();
        bool IsFree();
        Player* GetPlayer();

    protected:

    private:
        Location* location;
        Location* previous_location;
        Trajectory* trajectory;
};

#endif // BALL_H
