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

COIN_RESULT CoinFlipper::FlipPorc(int sides, int prob)
{
    //srand(time(NULL)); //inicializo la semilla
    random_device seeder;
    mt19937 engine(seeder());
    uniform_int_distribution<int>dist(1, sides);
    int secret = dist(engine);
    //int secret = rand() % sides + 1; //resultado está entre 1 y NUMBER_OF_SIDES
    if(secret <= prob)
    {
        return COIN_RESULT::WIN;
    }
    else
    {
        return COIN_RESULT::LOSE;
    }
}

int CoinFlipper::GetNumber(int max)
{
    srand(time(NULL)); //inicializo la semilla
    int secret = rand() % max;
}
