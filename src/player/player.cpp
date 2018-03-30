#include "player.h"

Player::Player()
{
    this->location = new Location(960, 540, 0);
}

Player::~Player()
{
    std::cout << "Destructor de Player" << "\n";
    delete location;
}

void Player::MoveLeft() {
    location->UpdateX(location->GetX() - PLAYER_SPEED);
    this->direction = WEST;
}

void Player::MoveRight() {
    location->UpdateX(location->GetX() + PLAYER_SPEED);
    this->direction = EAST;
}

void Player::MoveUp() {
    location->UpdateY(location->GetY() - PLAYER_SPEED);
    this->direction = NORTH;
}

void Player::MoveDown() {
    location->UpdateY(location->GetY() + PLAYER_SPEED);
    this->direction = SOUTH;
}

void Player::MoveUpToRight()
{
    location->UpdateY(location->GetY() - PLAYER_SPEED);
    location->UpdateX(location->GetX() + PLAYER_SPEED);
    this->direction = NORTHEAST;
}

void Player::MoveUpToLeft()
{
    location->UpdateY(location->GetY() - PLAYER_SPEED);
    location->UpdateX(location->GetX() - PLAYER_SPEED);
    this->direction = NORTHWEST;
}

void Player::MoveDownToRight()
{
    location->UpdateY(location->GetY() + PLAYER_SPEED);
    location->UpdateX(location->GetX() + PLAYER_SPEED);
    this->direction = SOUTHEAST;
}

void Player::MoveDownToLeft()
{
    location->UpdateY(location->GetY() + PLAYER_SPEED);
    location->UpdateX(location->GetX() - PLAYER_SPEED);
    this->direction = SOUTHWEST;
}

Location* Player::GetLocation() {
    return location;
}

DIRECTION Player::GetDirection()
{
    return this->direction;
}


