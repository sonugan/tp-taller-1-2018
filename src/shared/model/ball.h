#ifndef BALL_H
#define BALL_H

#include "location.h"
#include "player.h"
#include "keeper.h"
#include "trajectory.h"
#include <cstddef>
#include <chrono>
#include "../collision/circle.h"
#include "user-color.h"

class Keeper;
class Team;
class Trajectory;
class Player;
class Ball
{
    public:
        Ball();
        virtual ~Ball();
        Location* GetLocation();
        Location* GetPreviousLocation();
        void SetTrajectory(Trajectory* new_trajectory);
        void Move();
        bool IsFree();
        Player* GetPlayer();
        Keeper* GetKeeper();
        bool LastFreedDelayPassed();
        Circle* GetCircle();
        Trajectory* GetTrajectory();
        void SetLastOwner(Team* team, USER_COLOR color);
        USER_COLOR GetLastOwnerColor();
        Team* GetLastOwnerTeam();
        void ReturnToMiddle();
        static const int BALL_TRIDIMENSIONAL_OFFSET = 5;
        void BounceOnThrowIn();
        void BounceOnGoalPost();
        void GoToKeeper(Keeper* keeper);
        bool IsHeldByAnyKeeper();
    protected:

    private:
        static const unsigned int LAST_FREED_DELAY_MILLIS = 150;
        Location* location;
        Location* previous_location;
        Trajectory* trajectory;
        USER_COLOR last_owner_player_color;
        Team* last_owner_team;
        std::chrono::time_point<std::chrono::system_clock> last_freed;
        Circle* circle;
        static const u_int HALO_RADIUS = 10;
};

#endif // BALL_H
