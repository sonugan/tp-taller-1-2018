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
}

void Player::MoveRight(int pixels) {
    location->UpdateX(location->GetX() + pixels);
}

void Player::MoveUp(int pixels) {
    location->UpdateY(location->GetY() - pixels);
}

void Player::MoveDown(int pixels) {
    location->UpdateY(location->GetY() + pixels);
}

Location* Player::GetLocation() {
    return location;
}


