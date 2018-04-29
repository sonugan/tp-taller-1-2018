#include "player.h"
#include "../logger.h"

Player::Player(unsigned int position_index) {
    this->position_index = position_index;
    this->selected = false;
    this->direction = EAST;
}

Player::~Player()
{
    Logger::getInstance()->debug("DESTRUYENDO PLAYER");
    delete location;
}

void Player::MoveLeft(bool run) {
    this->direction = WEST;
    Move(run);
}

void Player::MoveRight(bool run)
{
    this->direction = EAST;
    Move(run);
}

void Player::MoveUp(bool run)
{
    this->direction = NORTH;
    Move(run);
}

void Player::MoveDown(bool run)
{
    this->direction = SOUTH;
    Move(run);
}

void Player::MoveUpToRight(bool run)
{
    this->direction = NORTHEAST;
    Move(run);
}

void Player::MoveUpToLeft(bool run)
{
    this->direction = NORTHWEST;
    Move(run);
}

void Player::MoveDownToRight(bool run)
{
    this->direction = SOUTHEAST;
    Move(run);
}

void Player::MoveDownToLeft(bool run)
{
    this->direction = SOUTHWEST;
    Move(run);
}

void Player::Kick()
{
    this->kicking = true;
}

void Player::RecoverBall()
{
    this->recoveringBall = true;
    this->Move(false);
}

Location* Player::GetLocation() {
    return location;
}

DIRECTION Player::GetDirection()
{
    return this->direction;
}

void Player::SetSelected(bool value) {
    this->selected = value;
}

Location* Player::GetDefaultLocation() {
    return team->GetFormation()->GetLocationForPlayer(position_index);

}

void Player::SetTeam(Team* team) {
    this->team = team;
    Location* default_location = GetDefaultLocation();
    this->location = new Location(default_location->GetX(), default_location->GetY(), default_location->GetZ());
}

unsigned int Player::GetPositionIndex() {
    return this->position_index;
}

bool Player::IsSelected() {
    return selected;
}

void Player::GoBackToDefaultPosition() {
    Location* default_location = team->GetFormation()->GetLocationForPlayer(position_index);
    int default_x = default_location->GetX();
    int x = location->GetX();
    int default_y = default_location->GetY();
    int y = location->GetY();
    if (x > default_x && y > default_y) {
        MoveUpToLeft(false);
    } else if (x < default_x && y > default_y) {
        MoveUpToRight(false);
    } else if (x < default_x && y < default_y) {
        MoveDownToRight(false);
    } else if (x > default_x && y < default_y) {
        MoveDownToLeft(false);
    } else if (x > default_x && y == default_y) {
        MoveLeft(false);
    } else if (x < default_x && y == default_y) {
        MoveRight(false);
    } else if (x == default_x && y > default_y) {
        MoveUp(false);
    } else if (x == default_x && y < default_y) {
        MoveDown(false);
    }else{
        direction = EAST;//TODO: cuando haya mas equipos debe quedar mirando para otro lado
    }

    if (abs(default_y - location->GetY()) < PLAYER_SPEED) {
        location->UpdateY(default_location->GetY());
    }
    if (abs(default_x - location->GetX()) < PLAYER_SPEED) {
        location->UpdateX(default_location->GetX());
    }
}

Team* Player::getTeam()
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

bool Player::IsRecoveringBall() {
    return recoveringBall;
}

void Player::SetRecoveringBall(bool recoveringBall) {
    this->recoveringBall = recoveringBall;
}

void Player::Move(bool run)
{
    int speed;
    if (recoveringBall) {
        speed = PLAYER_SPEED * 0.3;
    } else if (run) {
        speed = PLAYER_RUNNING_SPEED;
    } else {
        speed = PLAYER_SPEED;
    }

    switch(direction) {
        case NORTH:
            location->UpdateY(location->GetY() - speed);
        break;
        case WEST:
            location->UpdateX(location->GetX() - speed);
        break;
        case SOUTH:
            location->UpdateY(location->GetY() + speed);
        break;
        case EAST:
            location->UpdateX(location->GetX() + speed);
        break;
        case NORTHEAST:
            location->UpdateY(location->GetY() - speed);
            location->UpdateX(location->GetX() + speed);
        break;
        case NORTHWEST:
            location->UpdateY(location->GetY() - speed);
            location->UpdateX(location->GetX() - speed);
        break;
        case SOUTHEAST:
            location->UpdateY(location->GetY() + speed);
            location->UpdateX(location->GetX() + speed);
        break;
        case SOUTHWEST:
            location->UpdateY(location->GetY() + speed);
            location->UpdateX(location->GetX() - speed);
        break;
    }
}
