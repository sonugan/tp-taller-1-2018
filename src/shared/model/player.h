#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cmath>
#include "location.h"
#include "team.h"
#include "../configuration/configuration.h"
#include "trajectory.h"
#include "user-color.h"
#include "player-states/player-still-state.h"
#include "player-states/player-move-state.h"
#include "player-states/player-kick-state.h"
#include "player-states/player-recover-ball-state.h"

enum PLAYER_ACTION { PLAYER_IS_STILL, PLAYER_IS_KICKING, PLAYER_IS_RUNNING, PLAYER_IS_RECOVERING };
enum class DIRECTION { NORTH = 1, SOUTH = 2, EAST = 3, WEST = 4, NORTHEAST = 5, SOUTHEAST = 6, SOUTHWEST = 7, NORTHWEST = 8 };

class Team; //  forward declaration
class PlayerStillState;
class PlayerMoveState;
class PlayerKickState;
class PlayerRecoverBallState;
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
        void RecoverBall();
        Location* GetLocation();
        DIRECTION GetDirection();
        bool IsSelected();
        bool IsKicking();
        bool IsRecoveringBall();
        void SetKicking(bool kicking);
        void SetRecoveringBall(bool recoveringBall);
        Location* GetDefaultLocation();
        void SetTeam(Team* team);
        unsigned int GetPositionIndex();
        void GoBackToDefaultPosition();
        Team* GetTeam();
        bool HasBall();
        void PassBall();
        void CatchBall();
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

    protected:

    private:
        DIRECTION direction;
        static const int PLAYER_SPEED = 10;
        static const int PLAYER_RUNNING_SPEED = 15;
        static const int CATCH_DISTANCE = 50;
        USER_COLOR color;
        //bool kicking;
        bool recovering_ball;
        bool plays_for_team_a;
        bool plays_for_team_b;
        Team* team;
        unsigned int position_index;
        Location* location;
        PlayerStillState* still_state;
        PlayerMoveState* move_state;
        PlayerKickState* kick_state;
        PlayerRecoverBallState* recover_ball_state;
        IPlayerState* current_state;
};

#endif // PLAYER_H
