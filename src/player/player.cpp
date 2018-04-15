#include "player.h"
#include "logger.h"

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

void Player::MoveLeft() {
    this->direction = WEST;
    Move(PLAYER_SPEED);
}

void Player::MoveRight()
{
    this->direction = EAST;
    Move(PLAYER_SPEED);
}

void Player::MoveUp()
{
    this->direction = NORTH;
    Move(PLAYER_SPEED);
}

void Player::MoveDown()
{
    this->direction = SOUTH;
    Move(PLAYER_SPEED);
}

void Player::MoveUpToRight()
{
    this->direction = NORTHEAST;
    Move(PLAYER_SPEED);
}

void Player::MoveUpToLeft()
{
    this->direction = NORTHWEST;
    Move(PLAYER_SPEED);
}

void Player::MoveDownToRight()
{
    this->direction = SOUTHEAST;
    Move(PLAYER_SPEED);
}

void Player::MoveDownToLeft()
{
    this->direction = SOUTHWEST;
    Move(PLAYER_SPEED);
}

void Player::Kick()
{
    this->kicking = true;
}

void Player::RecoverBall()
{
    this->recoveringBall = true;
    this->Move(PLAYER_SPEED*0.3);
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

void Player::Move(int speed)
{
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
