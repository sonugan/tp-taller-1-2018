#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cmath>
#include "location.h"
#include "team.h"
#include "../configuration/configuration.h"
#include "trajectory.h"
#include "ball.h"
#include "user-color.h"
#include "player-states/player-still-state.h"
#include "player-states/player-move-state.h"
#include "player-states/player-kick-state.h"
#include "player-states/player-recover-ball-state.h"
#include "player-states/player-states.h"
#include "../collision/circle.h"
#include "../utils/coin-flipper.h"
#include "trajectory-type.h"

enum class DIRECTION { NORTH = 1, SOUTH = 2, EAST = 3, WEST = 4, NORTHEAST = 5, SOUTHEAST = 6, SOUTHWEST = 7, NORTHWEST = 8 };

class Team; //  forward declaration
class PlayerStillState;
class PlayerMoveState;
class PlayerKickState;
class PlayerRecoverBallState;
class IPlayerState;
class Player
{
    public:
        Player(unsigned int position_index, TEAM_NUMBER team_number);
        virtual ~Player();
        void MoveLeft(bool run);
        void MoveRight(bool run);
        void MoveUp(bool run);
        void MoveDown(bool run);
        void MoveUpToRight(bool run);
        void MoveUpToLeft(bool run);
        void MoveDownToRight(bool run);
        void MoveDownToLeft(bool run);
        void Kick();
        void LongPass(int power, TRAJECTORY_TYPE trajectory_type);
        void RecoverBall();
        Location* GetLocation();
        DIRECTION GetDirection();
        bool IsSelected();
        bool IsKicking();
        bool IsRecoveringBall();
        bool IsStill();
        bool IsMoving();
        PLAYER_ACTION GetCurrentAction();
        void SetCurrentAction(PLAYER_ACTION action);
        Location* GetDefaultLocation();
        void SetTeam(Team* team);
        unsigned int GetPositionIndex();
        void GoBackToDefaultPosition();
        Team* GetTeam();
        bool HasBall();
        void PassBall(Location* nearestPlayer);
        void KickBall(int power);
        bool PlaysForTeamA();
        bool PlaysForTeamB();
        void SetPlayerColor(USER_COLOR color);
        void SetDirection(DIRECTION direction);
        USER_COLOR GetPlayerColor();

        void ChangeToMove();
        void ChangeToKick();
        void ChangeToRecover();
        void ChangeToPass();
        void ChangeToCatchBall();
        void ChangeToStill();

        void Move(bool run);
        void Play();
        void SetIsStill(bool is_still);
        bool GetIsStill();
        void SetLocation(Location* location);
        Circle* GetCircle();
        bool AreInSameTeam(Player* player);
        bool TryRecover();
    protected:

    private:
        DIRECTION direction;
	static const int PLAYER_SPEED = 6;
	static const int PLAYER_RUNNING_SPEED = 10;
        USER_COLOR color;
        bool plays_for_team_a;
        bool plays_for_team_b;
        Team* team;
        unsigned int position_index;
        Location* location;
        Location* previous_location;
        PlayerStillState* still_state;
        PlayerMoveState* move_state;
        PlayerKickState* kick_state;
        PlayerRecoverBallState* recover_ball_state;
        IPlayerState* current_state;
        bool is_still;
	    Circle* circle;
        CoinFlipper* coin_flipper;
        static const u_int HALO_RADIUS = 10;
        unsigned int height = 64;
};

#endif // PLAYER_H
