#include "player.h"

Player::Player(unsigned int position_index) {
    this->position_index = position_index;
    this->selected = false;
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

void Player::Kick()
{
    this->kicking = true;
}

void Player::RecoverBall()
{
    this->recoveringBall = true;
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
        MoveUpToLeft();
    } else if (x < default_x && y > default_y) {
        MoveUpToRight();
    } else if (x < default_x && y < default_y) {
        MoveDownToRight();
    } else if (x > default_x && y < default_y) {
        MoveDownToLeft();
    } else if (x > default_x && y == default_y) {
        MoveLeft();
    } else if (x < default_x && y == default_y) {
        MoveRight();
    } else if (x == default_x && y > default_y) {
        MoveUp();
    } else if (x == default_x && y < default_y) {
        MoveDown();
    }

    if (abs(default_y - location->GetY()) < PLAYER_SPEED) {
        location->UpdateY(default_location->GetY());
    }
    if (abs(default_x - location->GetX()) < PLAYER_SPEED) {
        location->UpdateX(default_location->GetX());
    }

}

bool Player::IsKicking() {
    return kicking;
}

void Player::SetKicking(bool kicking) {
    this->kicking = kicking;
}

bool Player::IsRecoveringBall() {
    return recoveringBall;
}

void Player::SetRecoveringBall(bool recoveringBall) {
    this->recoveringBall = recoveringBall;
}
