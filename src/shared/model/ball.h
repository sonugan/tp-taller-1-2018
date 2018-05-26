#ifndef BALL_H
#define BALL_H

#include "location.h"
#include "player.h"
#include "trajectory.h"
#include <cstddef>
#include <chrono>

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
        bool LastFreedDelayPassed();

    protected:

    private:
        static const unsigned int LAST_FREED_DELAY_MILLIS = 300;
        Location* location;
        Location* previous_location;
        Trajectory* trajectory;
        std::chrono::time_point<std::chrono::system_clock> last_freed;
};

#endif // BALL_H
