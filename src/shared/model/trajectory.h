#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "player.h"

class Player;
enum class DIRECTION;
class Trajectory
{
    public:
        Trajectory(DIRECTION direction, unsigned int drive);
        Trajectory(Player* player);
        virtual ~Trajectory();
        void UpdateToNextLocation(Location* location);
        Player* GetPlayer();

    protected:

    private:
        static const int DIAGONAL_PLAYER_DIRECTION_OFFSET = 18;
        static const int NON_DIAGONAL_PLAYER_DIRECTION_OFFSET = 20;
        static const int DECELERATION = 6;
        static constexpr float DRIVE_COEFFICIENT = 0.08;

        DIRECTION direction;
        unsigned int drive;
        Player* player;
};

#endif // TRAJECTORY_H
