#include "trajectory.h"

Trajectory::Trajectory(DIRECTION direction, unsigned int power, TRAJECTORY_TYPE trajectory_type) {
    this->direction = direction;
    this->power = power;
    this->player = NULL;
    this->drive = 250;
    this->trajectory_type = trajectory_type;
    this->original_ball_speed = this->drive * this->power;
    this->ball_speed = this->original_ball_speed;
    this->direction_updated = false;
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
        int x, y, z, offset;
        x = location ->GetX();
        y = location->GetY();
        z = location->GetZ();
        offset = (ball_speed * DRIVE_COEFFICIENT);

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

        if (this->trajectory_type == TRAJECTORY_TYPE::UPWARDS)
        {
            z = z + offset;
        }

        if (this->trajectory_type == TRAJECTORY_TYPE::DOWNWARDS)
        {
            z = z - (offset*3);
        }


        if (this->ball_speed >= DECELERATION) {
            this->ball_speed = ball_speed - DECELERATION;
        } else {
            this->ball_speed = 0;
        }

        location->Update(x, y, z);
        if ((this->ball_speed <= this->original_ball_speed/2) && (this->trajectory_type == TRAJECTORY_TYPE::UPWARDS))
        {
            this->ChangeTrajectoryType(TRAJECTORY_TYPE::DOWNWARDS);
        }

        if(location->GetZ() <= 0)
        {
            z = 0;
            location->UpdateZ(z);
            this->ChangeTrajectoryType(TRAJECTORY_TYPE::FLOOR);

        }
    }
}

Player* Trajectory::GetPlayer() {
    return player;
}

TRAJECTORY_TYPE Trajectory::GetTrajectoryType(){
    return this->trajectory_type;
}

void Trajectory::ChangeTrajectoryType(TRAJECTORY_TYPE trajectory_type)
{
    this->trajectory_type = trajectory_type;
}

void Trajectory::UpdateTrajectoryType(TRAJECTORY_TYPE trajectory_type)
{
    if (this->trajectory_type != trajectory_type)
    {
        this->trajectory_type = trajectory_type;
    }
}

DIRECTION Trajectory::GetDirection()
{
    return this->direction;
}

void Trajectory::UpdateDirection(DIRECTION direction)
{
    if (!this->direction_updated)
    {
        this->direction = direction;
        this->direction_updated = true;
    }
}

unsigned int Trajectory::GetBallSpeed()
{
    return this->ball_speed;
}

void Trajectory::UpdateBallSpeed(unsigned int ball_speed)
{
    this->ball_speed = ball_speed;
}
