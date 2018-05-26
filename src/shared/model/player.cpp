#include "player.h"
#include "../logger.h"

Player::Player(unsigned int position_index, TEAM_NUMBER team_number)
{
    this->position_index = position_index;
    this->still_state = new PlayerStillState(this);
    this->move_state = new PlayerMoveState(this);
    this->kick_state = new PlayerKickState(this);
    this->recover_ball_state = new PlayerRecoverBallState(this);

    this->current_state = this->still_state;

    switch (team_number)
    {
    case TEAM_NUMBER::TEAM_A:
        this->direction = DIRECTION::EAST;
        this->plays_for_team_a = true;
        this->plays_for_team_b = false;
        break;
    case TEAM_NUMBER::TEAM_B:
        this->direction = DIRECTION::WEST;
        this->plays_for_team_b = true;
        this->plays_for_team_a = false;
        break;
    }

    this->color = USER_COLOR::NO_COLOR;

}

Player::~Player()
{
    Logger::getInstance()->debug("DESTRUYENDO PLAYER");
    delete location;
    delete still_state;
    delete move_state;
    delete kick_state;
    delete recover_ball_state;
}

void Player::MoveLeft(bool run)
{
    this->direction = DIRECTION::WEST;
    Move(run);
}

void Player::MoveRight(bool run)
{
    this->direction = DIRECTION::EAST;
    Move(run);
}

void Player::MoveUp(bool run)
{
    this->current_state->MoveUp(run);
}

void Player::MoveDown(bool run)
{
    this->current_state->MoveDown(run);
}

void Player::MoveUpToRight(bool run)
{
    this->current_state->MoveUpToRight(run);
}

void Player::MoveUpToLeft(bool run)
{
    this->current_state->MoveUpToLeft(run);
}

void Player::MoveDownToRight(bool run)
{
    this->current_state->MoveDownToRight(run);
}

void Player::MoveDownToLeft(bool run)
{
    this->current_state->MoveDownToLeft(run);
}

void Player::Kick()
{
    this->current_state->Kick();
    //this->kicking = true;
}

void Player::RecoverBall()
{
    this->current_state->RecoverBall();
    //this->recovering_ball = true;
    //this->Move(false);
}

Location* Player::GetLocation()
{
    return location;
}

DIRECTION Player::GetDirection()
{
    return this->direction;
}

Location* Player::GetDefaultLocation()
{
    return team->GetFormation()->GetLocationForPlayer(position_index);
}

void Player::SetTeam(Team* team)
{
    this->team = team;
    Location* default_location = GetDefaultLocation();
    this->location = new Location(default_location->GetX(), default_location->GetY(), default_location->GetZ());
}

unsigned int Player::GetPositionIndex()
{
    return this->position_index;
}

bool Player::HasBall()
{
    Player* player_with_ball = team->GetMatch()->GetBall()->GetPlayer();
    return (player_with_ball != NULL) && (this->GetPositionIndex() == player_with_ball->GetPositionIndex());
}

bool Player::IsSelected()
{
    return this->color != USER_COLOR::NO_COLOR;
}

void Player::GoBackToDefaultPosition()
{
    Location* default_location = team->GetFormation()->GetLocationForPlayer(position_index);
    int default_x = default_location->GetX();
    int x = location->GetX();
    int default_y = default_location->GetY();
    int y = location->GetY();
    if (x > default_x && y > default_y)
    {
        MoveUpToLeft(false);
    }
    else if (x < default_x && y > default_y)
    {
        MoveUpToRight(false);
    }
    else if (x < default_x && y < default_y)
    {
        MoveDownToRight(false);
    }
    else if (x > default_x && y < default_y)
    {
        MoveDownToLeft(false);
    }
    else if (x > default_x && y == default_y)
    {
        MoveLeft(false);
    }
    else if (x < default_x && y == default_y)
    {
        MoveRight(false);
    }
    else if (x == default_x && y > default_y)
    {
        MoveUp(false);
    }
    else if (x == default_x && y < default_y)
    {
        MoveDown(false);
    }
    else
    {
        if (this->plays_for_team_a)
        {
            direction = DIRECTION::EAST;
        }
        else
        {
            direction = DIRECTION::WEST;
        }
    }

    if (abs(default_y - location->GetY()) < PLAYER_SPEED)
    {
        location->UpdateY(default_location->GetY());
    }
    if (abs(default_x - location->GetX()) < PLAYER_SPEED)
    {
        location->UpdateX(default_location->GetX());
    }
}

Team* Player::GetTeam()
{
    return this->team;
}

bool Player::IsKicking()
{
    return this->current_state->IsKicking();
}

bool Player::IsStill()
{
    return this->current_state->IsStill();
}

bool Player::IsMoving()
{
    return this->current_state->IsMoving();
}

bool Player::IsRecoveringBall()
{
    return this->current_state->IsRecoveringBall();
}

void Player::Move(bool run)
{
    int speed;
    if (this->IsRecoveringBall())
    {
        speed = PLAYER_SPEED * 0.3;
    }
    else if (run)
    {
        speed = PLAYER_RUNNING_SPEED;
    }
    else
    {
        speed = PLAYER_SPEED;
    }

    switch(direction)
    {
    case DIRECTION::NORTH:
        location->UpdateY(location->GetY() - speed);
        break;
    case DIRECTION::WEST:
        location->UpdateX(location->GetX() - speed);
        break;
    case DIRECTION::SOUTH:
        location->UpdateY(location->GetY() + speed);
        break;
    case DIRECTION::EAST:
        location->UpdateX(location->GetX() + speed);
        break;
    case DIRECTION::NORTHEAST:
        location->UpdateY(location->GetY() - speed);
        location->UpdateX(location->GetX() + speed);
        break;
    case DIRECTION::NORTHWEST:
        location->UpdateY(location->GetY() - speed);
        location->UpdateX(location->GetX() - speed);
        break;
    case DIRECTION::SOUTHEAST:
        location->UpdateY(location->GetY() + speed);
        location->UpdateX(location->GetX() + speed);
        break;
    case DIRECTION::SOUTHWEST:
        location->UpdateY(location->GetY() + speed);
        location->UpdateX(location->GetX() - speed);
        break;
    }
}

void Player::CatchBall()
{
    if (!this->HasBall())
    {
        Ball* ball = team->GetMatch()->GetBall();
        int distance = ball->GetLocation()->Distance(location);
        if (ball->IsFree() && distance < CATCH_DISTANCE)
        {
            Trajectory* trajectory = new Trajectory(this);
            ball->SetTrajectory(trajectory);
            Player* previously_selected_player = team->GetSelectedPlayer();
            if (previously_selected_player != NULL && previously_selected_player->GetPositionIndex() != this->position_index)
            {
                previously_selected_player->SetPlayerColor(USER_COLOR::NO_COLOR);
            }
        }
    }
}

void Player::PassBall()
{
    if (HasBall())
    {
        Trajectory* trajectory = new Trajectory(direction, 250);
        team->GetMatch()->GetBall()->SetTrajectory(trajectory);
    }
}

bool Player::PlaysForTeamA()
{
    return this->plays_for_team_a;
}

bool Player::PlaysForTeamB()
{
    return this->plays_for_team_b;
}

void Player::SetPlayerColor(USER_COLOR color)
{
    this->color = color;
}

void Player::SetDirection(DIRECTION direction)
{
    this->direction = direction;
}

USER_COLOR Player::GetPlayerColor()
{
    return this->color;
}

void Player::ChangeToMove()
{
    this->current_state = this->move_state;
}
void Player::ChangeToKick()
{
    this->current_state = this->kick_state;
}
void Player::ChangeToRecover()
{
    this->current_state = this->recover_ball_state;
}
void Player::ChangeToPass()
{

}
void Player::ChangeToCatchBall()
{

}
void Player::ChangeToStill()
{
    this->current_state = this->still_state;
}

void Player::Play()
{
    this->current_state->Play();
}

PLAYER_ACTION Player::GetCurrentAction()
{
    return this->current_state->GetName();
}

void Player::SetCurrentAction(PLAYER_ACTION action)
{
    switch (action) {
        case PLAYER_ACTION::PLAYER_IS_KICKING:
            this->current_state = kick_state;
            break;
        case PLAYER_ACTION::PLAYER_IS_RECOVERING:
            this->current_state = recover_ball_state;
            break;
        case PLAYER_ACTION::PLAYER_IS_RUNNING:
            this->current_state = move_state;
            break;
        default:
            this->current_state = still_state;
            break;
    }
}
