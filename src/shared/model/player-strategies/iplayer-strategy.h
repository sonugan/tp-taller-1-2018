#ifndef IPLAYER_STRATEGY_H
#define IPLAYER_STRATEGY_H

#include "player-states.h"

class IPlayerStrategy
{
    public:
        void virtual Play(){};
        bool virtual IsRunningToArea(){ return false;};
    protected:
    private:

};

#endif // IPLAYER_STRATEGY_H
