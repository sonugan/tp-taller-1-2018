#ifndef PLAYER_MOVE_STATE_H
#define PLAYER_MOVE_STATE_H

#include "iplayer-state.h"
#include "../player.h"
#include "player-states.h"

class Player;
class PlayerMoveState : public IPlayerState
{
    public:
        PlayerMoveState(Player* player);
        virtual ~PlayerMoveState();
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
        bool IsStill() { return false; }
        bool IsMoving() { return true; }
        PLAYER_ACTION GetName(){ return PLAYER_ACTION::PLAYER_IS_RUNNING; }
    protected:
        Player* player;
    private:
};

#endif // PLAYER_MOVE_STATE_H
