#include "player-move-state.h"

PlayerMoveState::PlayerMoveState(Player* player)
{
    this->player = player;
    this->coin_flipper = new CoinFlipper();
}
PlayerMoveState::~PlayerMoveState()
{
    delete this->coin_flipper;
}
void PlayerMoveState::MoveLeft(bool run)
{
    this->player->SetDirection(DIRECTION::WEST);
    this->player->Move(run);
    this->has_been_moved = STATE_COUNTER_RESET_VALUE;
}
void PlayerMoveState::MoveRight(bool run)
{
    this->player->SetDirection(DIRECTION::EAST);
    this->player->Move(run);
    this->has_been_moved = STATE_COUNTER_RESET_VALUE;
}
void PlayerMoveState::MoveUp(bool run)
{
    this->player->SetDirection(DIRECTION::NORTH);
    this->player->Move(run);
    this->has_been_moved = STATE_COUNTER_RESET_VALUE;
}
void PlayerMoveState::MoveDown(bool run)
{
    this->player->SetDirection(DIRECTION::SOUTH);
    this->player->Move(run);
    this->has_been_moved = STATE_COUNTER_RESET_VALUE;
}
void PlayerMoveState::MoveUpToRight(bool run)
{
    this->player->SetDirection(DIRECTION::NORTHEAST);
    this->player->Move(run);
    this->has_been_moved = STATE_COUNTER_RESET_VALUE;
}
void PlayerMoveState::MoveUpToLeft(bool run)
{
    this->player->SetDirection(DIRECTION::NORTHWEST);
    this->player->Move(run);
    this->has_been_moved = STATE_COUNTER_RESET_VALUE;
}
void PlayerMoveState::MoveDownToRight(bool run)
{
    this->player->SetDirection(DIRECTION::SOUTHEAST);
    this->player->Move(run);
    this->has_been_moved = STATE_COUNTER_RESET_VALUE;
}
void PlayerMoveState::MoveDownToLeft(bool run)
{
    this->player->SetDirection(DIRECTION::SOUTHWEST);
    this->player->Move(run);
    this->has_been_moved = STATE_COUNTER_RESET_VALUE;
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
}

void PlayerMoveState::Play()
{
    //TODO
    if(has_been_moved == 0)
    {
        this->player->SetLocation(this->player->GetLocation());
    }
    else
    {
        this->has_been_moved--;
    }
    this->TryRecover();
}

void PlayerMoveState::TryRecover()
{
    Ball* ball = this->player->GetTeam()->GetMatch()->GetBall();
    if(!this->player->HasBall()
        && !this->player->AreInSameTeam(ball->GetPlayer())
        && ball->GetCircle()->ExistsCollision2d(this->player->GetCircle()))
    {
        if(this->coin_flipper->Flip() == COIN_RESULT::WIN)
        {
            Trajectory* trajectory = new Trajectory(this->player);
            ball->SetTrajectory(trajectory);
            this->player->ChangeToMove();
        }
    }
}
