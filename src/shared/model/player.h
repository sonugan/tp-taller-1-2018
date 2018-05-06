#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cmath>
#include "location.h"
#include "team.h"


enum PLAYER_ACTION { PLAYER_IS_STILL, PLAYER_IS_KICKING, PLAYER_IS_RUNNING, PLAYER_IS_RECOVERING };
enum class DIRECTION { NORTH, SOUTH, EAST, WEST, NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST };
class Team; //  forward declaration
class Player
{
    public:
        Player(unsigned int position_index);
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
        void SetSelected(bool value);
        void SetKicking(bool kicking);
        void SetRecoveringBall(bool recoveringBall);
        Location* GetDefaultLocation();
        void SetTeam(Team* team);
        unsigned int GetPositionIndex();
        void GoBackToDefaultPosition();
        Team* getTeam();
        bool HasBall();
        void SetHasBall(bool has_ball);
    protected:

    private:
        DIRECTION direction;
        static const int PLAYER_SPEED = 10;
        static const int PLAYER_RUNNING_SPEED = 15;
        bool selected;
        bool kicking;
        bool recovering_ball;
        bool has_ball;
        Team* team;
        unsigned int position_index;
        void Move(bool run);
        Location* location;
};

#endif // PLAYER_H
