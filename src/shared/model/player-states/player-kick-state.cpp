#include "player-kick-state.h"

PlayerKickState::PlayerKickState(Player* player)
{
    this->player = player;
    this->timming = 0;
    this->frames_per_event = PlayerView::FRAMES_PER_EVENT;
    this->frames_count = PlayerView::KICKING_FRAME_COUNT;
}
PlayerKickState::~PlayerKickState()
{

}
void PlayerKickState::MoveLeft(bool run)
{
    if(!ContinueKicking())
    {
        this->player->ChangeToStill();
        this->player->MoveLeft(run);
    }
}
void PlayerKickState::MoveRight(bool run)
{
    if(!ContinueKicking())
    {
        this->player->ChangeToStill();
        this->player->MoveRight(run);
    }
}
void PlayerKickState::MoveUp(bool run)
{
    if(!ContinueKicking())
    {
        this->player->ChangeToStill();
        this->player->MoveUp(run);
    }
}
void PlayerKickState::MoveDown(bool run)
{
    if(!ContinueKicking())
    {
        this->player->ChangeToStill();
        this->player->MoveDown(run);
    }
}
void PlayerKickState::MoveUpToRight(bool run)
{
    if(!ContinueKicking())
    {
        this->player->ChangeToStill();
        this->player->MoveUpToRight(run);
    }
}
void PlayerKickState::MoveUpToLeft(bool run)
{
    if(!ContinueKicking())
    {
        this->player->ChangeToStill();
        this->player->MoveUpToLeft(run);
    }
}
void PlayerKickState::MoveDownToRight(bool run)
{
    if(!ContinueKicking())
    {
        this->player->ChangeToStill();
        this->player->MoveDownToRight(run);
    }
}
void PlayerKickState::MoveDownToLeft(bool run)
{
    if(!ContinueKicking())
    {
        this->player->ChangeToStill();
        this->player->MoveDownToLeft(run);
    }
}
void PlayerKickState::Kick()
{
    ContinueKicking();
}
void PlayerKickState::RecoverBall()
{
    if(!ContinueKicking())
    {
        this->player->ChangeToRecover();
        this->player->RecoverBall();
    }
}
void PlayerKickState::PassBall()
{
    if(!ContinueKicking())
    {
        this->player->ChangeToPass();
        this->player->PassBall();
    }
}
void PlayerKickState::CatchBall()
{
    if(!ContinueKicking())
    {
        this->player->ChangeToCatchBall();
        //this->player->CatchBall();
    }
}

bool PlayerKickState::ContinueKicking()
{
    this->timming++;
    if((this->timming * this->frames_per_event) < this->frames_count)
    {
        return true;
    }
    else
    {
        this->timming = 0;
        return false;
    }
}

void PlayerKickState::Play()
{
    if(!ContinueKicking())
    {
        this->player->ChangeToStill();
    }
}
