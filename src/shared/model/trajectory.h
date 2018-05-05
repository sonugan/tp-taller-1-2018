#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "player.h"

class Player;
enum class DIRECTION;
class Trajectory
{
    public:
        Trajectory();
        Trajectory(Player* player);
        virtual ~Trajectory();

    protected:

    private:
        DIRECTION direction;
        Player* player;
};

#endif // TRAJECTORY_H
