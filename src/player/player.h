#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "../common/location.h"
#include "../common/ilocatable.h"


enum DIRECTION { NORTH, SOUTH, EAST, WEST, NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST };
class Player : public ILocatable
{
    public:
        Player();
        virtual ~Player();
        void MoveLeft(int pixels);
        void MoveRight(int pixels);
        void MoveUp(int pixels);
        void MoveDown(int pixels);
        Location* GetLocation();
        DIRECTION GetDirection();
    protected:

    private:
        DIRECTION direction;
};

#endif // PLAYER_H
