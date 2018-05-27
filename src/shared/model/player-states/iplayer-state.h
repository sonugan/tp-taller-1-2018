#ifndef IPLAYER_STATE_H
#define IPLAYER_STATE_H

//#include "../player.h"
#include "player-states.h"

class IPlayerState
{
    public:
        void virtual MoveLeft(bool run){};
        void virtual MoveRight(bool run){};
        void virtual MoveUp(bool run){};
        void virtual MoveDown(bool run){};
        void virtual MoveUpToRight(bool run){};
        void virtual MoveUpToLeft(bool run){};
        void virtual MoveDownToRight(bool run){};
        void virtual MoveDownToLeft(bool run){};
        void virtual Kick(){};
        void virtual RecoverBall(){};
        void virtual PassBall(){};
        void virtual CatchBall(){};
        void virtual Play(){};
        bool virtual IsKicking(){ return false; }
        bool virtual IsRecoveringBall() { return false; }
        PLAYER_ACTION virtual GetName(){ return PLAYER_ACTION::PLAYER_IS_STILL; }
    protected:
    private:

};

#endif // IPLAYER_STATE_H
