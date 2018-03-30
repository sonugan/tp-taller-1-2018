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
        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void MoveUpToRight();
        void MoveUpToLeft();
        void MoveDownToRight();
        void MoveDownToLeft();
        Location* GetLocation();
        DIRECTION GetDirection();
    protected:

    private:
        DIRECTION direction;
        static const int PLAYER_SPEED = 10;
};

#endif // PLAYER_H
