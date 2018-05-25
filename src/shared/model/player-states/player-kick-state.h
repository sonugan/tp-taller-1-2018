#ifndef PLAYERKICKSTATE_H
#define PLAYERKICKSTATE_H

#include "../../client/view/player-view.h"
#include "iplayer-state.h"
#include "../player.h"

class Player;
class PlayerKickState : public IPlayerState
{
    public:
        PlayerKickState(Player* player);
        virtual ~PlayerKickState();
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
        bool IsKicking(){ return true; }
        bool IsRecoveringBall() { return false; }
    protected:
        Player* player;
    private:
        u_int timming;
        bool ContinueKicking();
        u_int frames_per_event;
        u_int frames_count;
};

#endif // PLAYERKICKSTATE_H
