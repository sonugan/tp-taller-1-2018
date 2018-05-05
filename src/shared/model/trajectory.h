#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "shared-enums.h"

class Trajectory
{
    public:
        Trajectory();
        virtual ~Trajectory();

    protected:

    private:
        DIRECTION direction;
};

#endif // TRAJECTORY_H
