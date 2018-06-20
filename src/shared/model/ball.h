#ifndef BALL_H
#define BALL_H

#include "location.h"
#include "player.h"
#include "trajectory.h"
#include <cstddef>
#include <chrono>
#include <vector>
#include "../collision/circle.h"

using namespace std;

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
        Circle* GetCircle();
        void NotifyAllPlayers();
        void AddPlayerToObserve(Player* player);
    protected:

    private:
        static const unsigned int LAST_FREED_DELAY_MILLIS = 150;
        Location* location;
        Location* previous_location;
        Trajectory* trajectory;
        std::chrono::time_point<std::chrono::system_clock> last_freed;
        Circle* circle;
        static const u_int HALO_RADIUS = 10;
        vector<Player*> players;
};

#endif // BALL_H
