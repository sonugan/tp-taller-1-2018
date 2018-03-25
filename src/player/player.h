#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "../common/location.h"

class Player
{
    public:
        Player();
        virtual ~Player();
        void MoveLeft(int pixels);
        void MoveRight(int pixels);
        void MoveUp(int pixels);
        void MoveDown(int pixels);
        Location* GetLocation();

    protected:

    private:
        Location* location;
};

#endif // PLAYER_H
