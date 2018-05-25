#ifndef PLAYER_STILL_STATE_H
#define PLAYER_STILL_STATE_H

#include "iplayer-state.h"
#include "../player.h"

class Player;
class PlayerStillState : public IPlayerState
{
    public:
        PlayerStillState(Player* player);
        virtual ~PlayerStillState();
        void MoveLeft(bool run);
        void MoveRight(bool run);
        void MoveUp(bool run);
        void MoveDown(bool run);
        void MoveUpToRight(bool run);
        void MoveUpToLeft(bool run);
        void MoveDownToRight(bool run);
        void MoveDownToLeft(bool run);
        void Kick();
        void RecoverBall();
        void PassBall();
        void CatchBall();
        void Play();
        bool IsKicking(){ return false; }
        bool IsRecoveringBall() { return false; }
    protected:
        Player* player;
        IPlayerState* state;
    private:
};

#endif // PLAYER_STILL_STATE_H
