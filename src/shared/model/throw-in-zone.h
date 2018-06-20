#ifndef THROW_IN_ZONE_H
#define THROW_IN_ZONE_H

#include "ipitch-zone.h"

class Team;
class Ball;
class ThrowInZone : public iPitchZone
{
    public:
        ThrowInZone(Location* top_left_corner, Location* bottom_right_corner);
        ~ThrowInZone();
        bool IsTouching(Ball* ball);

    protected:
    private:
};

#endif // THROW_IN_ZONE_H
