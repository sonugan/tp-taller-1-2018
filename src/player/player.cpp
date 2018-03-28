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

void Player::MoveLeft(int pixels) {
    location->UpdateX(location->GetX() - pixels);
    this->direction = WEST;
}

void Player::MoveRight(int pixels) {
    location->UpdateX(location->GetX() + pixels);
    this->direction = EAST;
}

void Player::MoveUp(int pixels) {
    location->UpdateY(location->GetY() - pixels);
    this->direction = NORTH;
}

void Player::MoveDown(int pixels) {
    location->UpdateY(location->GetY() + pixels);
    this->direction = SOUTH;
}

Location* Player::GetLocation() {
    return location;
}

DIRECTION Player::GetDirection()
{
    return this->direction;
}


