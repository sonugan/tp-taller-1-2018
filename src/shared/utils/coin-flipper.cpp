#include "coin-flipper.h"

CoinFlipper::CoinFlipper()
{

}

CoinFlipper::~CoinFlipper()
{

}

COIN_RESULT CoinFlipper::Flip()
{
    srand(time(NULL)); //inicializo la semilla
    int secret = rand() % CoinFlipper::NUMBER_OF_SIDES + 1; //resultado está entre 1 y NUMBER_OF_SIDES
    if(secret <= CoinFlipper::NUMBER_OF_SIDES / 2)
    {
        return COIN_RESULT::LOSE;
    }
    else
    {
        return COIN_RESULT::WIN;
    }
}
