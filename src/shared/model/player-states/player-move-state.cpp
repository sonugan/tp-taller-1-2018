#include "player-move-state.h"

PlayerMoveState::PlayerMoveState(Player* player)
{
    this->player = player;
}
PlayerMoveState::~PlayerMoveState()
{

}
void PlayerMoveState::MoveLeft(bool run)
{
    this->player->SetDirection(DIRECTION::WEST);
    this->player->Move(run);
}
void PlayerMoveState::MoveRight(bool run)
{
    this->player->SetDirection(DIRECTION::EAST);
    this->player->Move(run);
}
void PlayerMoveState::MoveUp(bool run)
{
    this->player->SetDirection(DIRECTION::NORTH);
    this->player->Move(run);
}
void PlayerMoveState::MoveDown(bool run)
{
    this->player->SetDirection(DIRECTION::SOUTH);
    this->player->Move(run);
}
void PlayerMoveState::MoveUpToRight(bool run)
{
    this->player->SetDirection(DIRECTION::NORTHEAST);
    this->player->Move(run);
}
void PlayerMoveState::MoveUpToLeft(bool run)
{
    this->player->SetDirection(DIRECTION::NORTHWEST);
    this->player->Move(run);
}
void PlayerMoveState::MoveDownToRight(bool run)
{
    this->player->SetDirection(DIRECTION::SOUTHEAST);
    this->player->Move(run);
}
void PlayerMoveState::MoveDownToLeft(bool run)
{
    this->player->SetDirection(DIRECTION::SOUTHWEST);
    this->player->Move(run);
}
void PlayerMoveState::Kick()
{
    this->player->ChangeToKick();
    this->player->Kick();
}
void PlayerMoveState::RecoverBall()
{
    this->player->ChangeToRecover();
    this->player->RecoverBall();
}
void PlayerMoveState::PassBall()
{
    this->player->ChangeToPass();
    this->player->PassBall();
}
void PlayerMoveState::CatchBall()
{
    this->player->ChangeToCatchBall();
    //this->player->CatchBall();
}

void PlayerMoveState::Play()
{
    //TODO
}
