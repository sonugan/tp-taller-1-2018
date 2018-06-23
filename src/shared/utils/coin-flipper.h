#ifndef COIN_FLIPPER_H
#define COIN_FLIPPER_H

#include <stdlib.h>
#include <ctime>
#include <iostream>

using namespace std;

enum class COIN_RESULT { WIN = 1, LOSE = 2 };
class CoinFlipper
{
    public:
        CoinFlipper();
        virtual ~CoinFlipper();
        COIN_RESULT Flip();
        COIN_RESULT FlipPorc(int sides, int prob);
        int GetNumber(int max);
    protected:
    private:
        static const int NUMBER_OF_SIDES = 2;
};

#endif // COIN_FLIPPER_H
