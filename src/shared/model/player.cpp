#include "player.h"
#include "../logger.h"

Player::Player(unsigned int position_index, TEAM_NUMBER team_number)
{
    this->position_index = position_index;
    this->kicking = false;
    this->recovering_ball = false;

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
    this->direction = DIRECTION::NORTH;
    Move(run);
}

void Player::MoveDown(bool run)
{
    this->direction = DIRECTION::SOUTH;
    Move(run);
}

void Player::MoveUpToRight(bool run)
{
    this->direction = DIRECTION::NORTHEAST;
    Move(run);
}

void Player::MoveUpToLeft(bool run)
{
    this->direction = DIRECTION::NORTHWEST;
    Move(run);
}

void Player::MoveDownToRight(bool run)
{
    this->direction = DIRECTION::SOUTHEAST;
    Move(run);
}

void Player::MoveDownToLeft(bool run)
{
    this->direction = DIRECTION::SOUTHWEST;
    Move(run);
}

void Player::Kick()
{
    this->kicking = true;
}

void Player::RecoverBall()
{
    this->recovering_ball = true;
    this->Move(false);
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
    //return (player_with_ball != NULL) && (this->GetPositionIndex() == player_with_ball->GetPositionIndex()) && (this->GetTeam()->GetName() == player_with_ball->GetTeam()->GetName());
    return this == player_with_ball;
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
    return kicking;
}

void Player::SetKicking(bool kicking)
{
    this->kicking = kicking;
}

bool Player::IsRecoveringBall()
{
    return recovering_ball;
}

void Player::SetRecoveringBall(bool recovering_ball)
{
    this->recovering_ball = recovering_ball;
}

void Player::Move(bool run)
{
    int speed;
    if (recovering_ball)
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

void Player::PassBall()
{
    if (HasBall())
    {
        //std::cout << "Player::PassBall \n";
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
