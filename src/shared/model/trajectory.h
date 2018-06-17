#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "player.h"
#include "trajectory-type.h"

class Player;
enum class DIRECTION;
class Trajectory
{
    public:
        Trajectory(DIRECTION direction, unsigned int drive, TRAJECTORY_TYPE trajectory_type);
        Trajectory(DIRECTION direction, unsigned int drive, TRAJECTORY_TYPE trajectory_type, Location* nearest_player);
        Trajectory(Player* player);
        virtual ~Trajectory();
        void UpdateToNextLocation(Location* location);
        Player* GetPlayer();
        TRAJECTORY_TYPE GetTrajectoryType();
        void ChangeTrajectoryType(TRAJECTORY_TYPE trajectory_type);
        void UpdateTrajectoryType(TRAJECTORY_TYPE trajectory_type);
        unsigned int GetBallSpeed();

    protected:

    private:
        static const int DIAGONAL_PLAYER_DIRECTION_OFFSET = 18;
        static const int NON_DIAGONAL_PLAYER_DIRECTION_OFFSET = 20;
        static const int DECELERATION = 6;
        static constexpr float DRIVE_COEFFICIENT = 0.08;

        DIRECTION direction;
        unsigned int power;
        unsigned int drive;
        unsigned int ball_speed;
        unsigned int original_ball_speed;
        Player* player;
        TRAJECTORY_TYPE trajectory_type;
        Location* nearest_player;
};

#endif // TRAJECTORY_H
