#include "trajectory.h"

Trajectory::Trajectory(DIRECTION direction, unsigned int power, TRAJECTORY_TYPE trajectory_type) {
    this->direction = direction;
    this->power = power;
    this->player = NULL;
    this->drive = 125;
    this->trajectory_type = trajectory_type;
    this->original_ball_speed = this->drive * this->power;
    this->ball_speed = this->original_ball_speed;
    this->nearest_player = NULL;
    //std::cout << "Trajectory::Trajectory created \n";
}

Trajectory::Trajectory(DIRECTION direction, unsigned int power, TRAJECTORY_TYPE trajectory_type, Location* nearest_player) {
    this->direction = direction;
    this->power = power;
    this->player = NULL;
    this->drive = 125;
    this->trajectory_type = trajectory_type;
    this->original_ball_speed = this->drive * this->power;
    this->ball_speed = this->original_ball_speed;
    this->nearest_player = nearest_player;
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

        if (nearest_player == NULL ){
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
        }else{
            int nearest_player_x = nearest_player->GetX();
            int nearest_player_y = nearest_player->GetY();
            if (DIRECTION::EAST == direction) {
                x = x + offset;
                if (offset > 1){
                    if (y > nearest_player_y){
                        y = y - 3;
                    }else if (y < nearest_player_y){
                        y = y + 3;
                    }
                }
            } else if (DIRECTION::WEST == direction) {
                x = x - offset;
                if (offset > 1){
                    if (y > nearest_player_y){
                        y = y - 3;
                    }else if (y < nearest_player_y){
                        y = y + 3;
                    }
                }
            } else if (DIRECTION::SOUTH == direction) {
                y = y + offset;
                if (offset > 1){
                    if (x > nearest_player_x){
                        x = x - 3;
                    }else if (x < nearest_player_x){
                        x = x + 3;
                    }
                }
            } else if (DIRECTION::NORTH == direction) {
                y = y - offset;
                if (offset > 1){
                    if (x > nearest_player_x){
                        x = x - 3;
                    }else if (x < nearest_player_x){
                        x = x + 3;
                    }
                }
            }else if (DIRECTION::NORTHEAST == direction) {
                x = x + offset;
                y = y - offset;
            } else if (DIRECTION::NORTHWEST == direction) {
                x = x - offset;
                y = y - offset;
            } else if (DIRECTION::SOUTHWEST == direction) {
                x = x - offset;
                y = y + offset;
            } else if (DIRECTION::SOUTHEAST == direction) {
                x = x + offset;
                y = y + offset;
            }

            if ((x == nearest_player_x) || (y == nearest_player_y)){
                this->nearest_player = NULL;
            }
        }

        if (this->trajectory_type == TRAJECTORY_TYPE::UPWARDS)
        {
            z = z + offset;
        }

        if (this->trajectory_type == TRAJECTORY_TYPE::DOWNWARDS)
        {
            z = z - (offset*2);
        }


        if (this->ball_speed >= DECELERATION) {
            this->ball_speed = ball_speed - DECELERATION;
        } else {
            this->ball_speed = 0;
        }

        location->Update(x, y, z);
        if ((this->ball_speed <= (this->original_ball_speed* 2/3)) && (this->trajectory_type == TRAJECTORY_TYPE::UPWARDS))
        {
            this->ChangeTrajectoryType(TRAJECTORY_TYPE::DOWNWARDS);
        }

        if (location->GetZ() <= 0)
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

unsigned int Trajectory::GetBallSpeed()
{
    return this->original_ball_speed;
}

void Trajectory::UpdateTrajectoryType(TRAJECTORY_TYPE trajectory_type)
{
    if (this->trajectory_type != trajectory_type)
    {
        this->trajectory_type = trajectory_type;
    }
}
