#include "player-still-state.h"

PlayerStillState::PlayerStillState(Player* player)
{
    this->player = player;
}
PlayerStillState::~PlayerStillState()
{

}
void PlayerStillState::MoveLeft(bool run)
{
    this->player->ChangeToMove();
    this->player->MoveLeft(run);
}
void PlayerStillState::MoveRight(bool run)
{
    this->player->ChangeToMove();
    this->player->MoveRight(run);
}
void PlayerStillState::MoveUp(bool run)
{
    this->player->ChangeToMove();
    this->player->MoveUp(run);
}
void PlayerStillState::MoveDown(bool run)
{
    this->player->ChangeToMove();
    this->player->MoveDown(run);
}
void PlayerStillState::MoveUpToRight(bool run)
{
    this->player->ChangeToMove();
    this->player->MoveUpToRight(run);
}
void PlayerStillState::MoveUpToLeft(bool run)
{
    this->player->ChangeToMove();
    this->player->MoveUpToLeft(run);
}
void PlayerStillState::MoveDownToRight(bool run)
{
    this->player->ChangeToMove();
    this->player->MoveDownToRight(run);
}
void PlayerStillState::MoveDownToLeft(bool run)
{
    this->player->ChangeToMove();
    this->player->MoveDownToLeft(run);
}
void PlayerStillState::Kick()
{
    this->player->ChangeToKick();
    this->player->Kick();
}
void PlayerStillState::RecoverBall()
{
    this->player->ChangeToRecover();
    this->player->RecoverBall();
}
void PlayerStillState::PassBall()
{
    this->player->ChangeToPass();
    this->player->PassBall();
}
void PlayerStillState::CatchBall()
{
    this->player->ChangeToCatchBall();
    //this->player->CatchBall();
}

void PlayerStillState::Play()
{
    this->player->SetLocation(this->player->GetLocation());
}
