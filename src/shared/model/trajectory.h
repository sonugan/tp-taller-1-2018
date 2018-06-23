#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "player.h"
#include "keeper.h"
#include "trajectory-type.h"

class Player;
class Keeper;
enum class DIRECTION;
class Trajectory
{
    public:
        Trajectory(DIRECTION direction, unsigned int drive, TRAJECTORY_TYPE trajectory_type);
        Trajectory(DIRECTION direction, unsigned int drive, TRAJECTORY_TYPE trajectory_type, Location* nearest_player);
        Trajectory(Player* player);
        Trajectory(Keeper* keeper);
        virtual ~Trajectory();
        void UpdateToNextLocation(Location* location);
        Player* GetPlayer();
        Keeper* GetKeeper();
        TRAJECTORY_TYPE GetTrajectoryType();
        void ChangeTrajectoryType(TRAJECTORY_TYPE trajectory_type);
        void UpdateTrajectoryType(TRAJECTORY_TYPE trajectory_type);
        DIRECTION GetDirection();
        void UpdateDirection(DIRECTION direction);
        unsigned int GetBallSpeed();
        unsigned int GetActualBallSpeed();
        void UpdateBallSpeed(unsigned int ball_speed);
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
        bool direction_updated;
        Player* player;
        Keeper* keeper;
        TRAJECTORY_TYPE trajectory_type;
        void UpdateToNextLocationForFreeTrajectory(Location* location);
        void UpdateToNextLocationForPlayerTrajectory(Location* location);
        void UpdateToNextLocationForKeeperTrajectory(Location* location);
        Location* nearest_player;
};

#endif // TRAJECTORY_H
