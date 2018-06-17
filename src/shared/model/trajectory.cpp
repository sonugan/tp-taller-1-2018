#include "trajectory.h"

Trajectory::Trajectory(DIRECTION direction, unsigned int drive) {
    this->direction = direction;
    this->drive = drive;
    this->player = NULL;
    //std::cout << "Trajectory::Trajectory created \n";
}

Trajectory::Trajectory(Player* player) {
    this->player = player;
}

Trajectory::~Trajectory() {

}

void Trajectory::UpdateToNextLocation(Location* location) {
    //std::cout << "Trajectory::UpdateToNextLocation \n";
    if (player != NULL) {
        //std::cout << "Trajectory::UpdateToNextLocation player != NULL \n";
        Location* player_location = player->GetLocation();
        direction = player->GetDirection();
        int x, y;
        x = player_location ->GetX();
        y = player_location->GetY();
        if (DIRECTION::EAST == direction) {
            x = x + NON_DIAGONAL_PLAYER_DIRECTION_OFFSET;
        } else if (DIRECTION::WEST == direction) {
            x = x - NON_DIAGONAL_PLAYER_DIRECTION_OFFSET;
        } else if (DIRECTION::SOUTH == direction) {
            y = y + NON_DIAGONAL_PLAYER_DIRECTION_OFFSET;
        } else if (DIRECTION::NORTH == direction) {
            y = y - NON_DIAGONAL_PLAYER_DIRECTION_OFFSET;
        } else if (DIRECTION::SOUTHWEST == direction) {
            x = x - DIAGONAL_PLAYER_DIRECTION_OFFSET;
            y = y + DIAGONAL_PLAYER_DIRECTION_OFFSET;
        } else if (DIRECTION::SOUTHEAST == direction) {
            x = x + DIAGONAL_PLAYER_DIRECTION_OFFSET;
            y = y + DIAGONAL_PLAYER_DIRECTION_OFFSET;
        } else if (DIRECTION::NORTHWEST == direction) {
            x = x - DIAGONAL_PLAYER_DIRECTION_OFFSET;
            y = y - DIAGONAL_PLAYER_DIRECTION_OFFSET;
        } else if (DIRECTION::NORTHEAST == direction) {
            x = x + DIAGONAL_PLAYER_DIRECTION_OFFSET;
            y = y - DIAGONAL_PLAYER_DIRECTION_OFFSET;
        }
        location->Update(x, y, player_location->GetZ());
    } else {
        int x, y, offset;
        x = location ->GetX();
        y = location->GetY();

        offset = (drive * DRIVE_COEFFICIENT);


        if (DIRECTION::EAST == direction) {
            x = x + offset;
        } else if (DIRECTION::WEST == direction) {
            x = x - offset;
        } else if (DIRECTION::SOUTH == direction) {
            y = y + offset;
        } else if (DIRECTION::NORTH == direction) {
            y = y - offset;
        } else if (DIRECTION::SOUTHWEST == direction) {
            x = x - offset;
            y = y + offset;
        } else if (DIRECTION::SOUTHEAST == direction) {
            x = x + offset;
            y = y + offset;
        } else if (DIRECTION::NORTHWEST == direction) {
            x = x - offset;
            y = y - offset;
        } else if (DIRECTION::NORTHEAST == direction) {
            x = x + offset;
            y = y - offset;
        }


        if (this->drive >= DECELERATION) {
            this->drive = drive - DECELERATION;
        } else {
            this->drive = 0;
        }

        location->Update(x, y, location->GetZ());
    }
}

Player* Trajectory::GetPlayer() {
    return player;
}

DIRECTION Trajectory::GetDirection()
{
    return this->direction;
}

void Trajectory::SetDirection(DIRECTION direction)
{
    this->direction = direction;
}

unsigned int Trajectory::GetDrive()
{
    return this->drive;
}

void Trajectory::SetDrive(unsigned int drive)
{
    this->drive = drive;
}
