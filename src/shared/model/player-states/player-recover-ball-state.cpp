#include "player-recover-ball-state.h"

PlayerRecoverBallState::PlayerRecoverBallState(Player* player)
{
    this->player = player;
    this->timming = 0;
    this->frames_per_event = PlayerView::FRAMES_PER_EVENT;
    this->frames_count = PlayerView::RECOVERING_FRAME_COUNT;
}
PlayerRecoverBallState::~PlayerRecoverBallState()
{
}
void PlayerRecoverBallState::MoveLeft(bool run)
{
    if(!ContinueRecovering())
    {
        this->player->ChangeToStill();
        this->player->MoveLeft(run);
    }
}
void PlayerRecoverBallState::MoveRight(bool run)
{
    if(!ContinueRecovering())
    {
        this->player->ChangeToStill();
        this->player->MoveRight(run);
    }
}
void PlayerRecoverBallState::MoveUp(bool run)
{
    if(!ContinueRecovering())
    {
        this->player->ChangeToStill();
        this->player->MoveUp(run);
    }
}
void PlayerRecoverBallState::MoveDown(bool run)
{
    if(!ContinueRecovering())
    {
        this->player->ChangeToStill();
        this->player->MoveDown(run);
    }
}
void PlayerRecoverBallState::MoveUpToRight(bool run)
{
    if(!ContinueRecovering())
    {
        this->player->ChangeToStill();
        this->player->MoveUpToRight(run);
    }
}
void PlayerRecoverBallState::MoveUpToLeft(bool run)
{
    if(!ContinueRecovering())
    {
        this->player->ChangeToStill();
        this->player->MoveUpToLeft(run);
    }
}
void PlayerRecoverBallState::MoveDownToRight(bool run)
{
    if(!ContinueRecovering())
    {
        this->player->ChangeToStill();
        this->player->MoveDownToRight(run);
    }
}
void PlayerRecoverBallState::MoveDownToLeft(bool run)
{
    if(!ContinueRecovering())
    {
        this->player->ChangeToStill();
        this->player->MoveDownToLeft(run);
    }
}
void PlayerRecoverBallState::Kick()
{
    if(!ContinueRecovering())
    {
        this->player->ChangeToKick();
        this->player->Kick();
    }
}
void PlayerRecoverBallState::RecoverBall()
{
    ContinueRecovering();
}
void PlayerRecoverBallState::PassBall()
{
    if(!ContinueRecovering())
    {
        this->player->ChangeToPass();
        this->player->PassBall(NULL);
    }
}
void PlayerRecoverBallState::CatchBall()
{
    if(!ContinueRecovering())
    {
        this->player->ChangeToCatchBall();
        //this->player->CatchBall();
    }
}

bool PlayerRecoverBallState::ContinueRecovering()
{
    this->timming++;
    if((this->timming * this->frames_per_event) < this->frames_count)
    {
        this->player->Move(false);
        return true;
    }
    else
    {
        this->timming = 0;
        return false;
    }
}

void PlayerRecoverBallState::Play()
{
    if(!ContinueRecovering())
    {
        this->timming = 0;
        this->player->ChangeToStill();
    }
    else
    {
        this->TryRecover();
        this->player->Move(false);
    }
}

void PlayerRecoverBallState::TryRecover()
{
    if(this->player->TryRecover())
    {
        this->timming = 0;
        this->player->ChangeToMove();
    }
}
