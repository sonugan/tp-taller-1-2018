#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cmath>
#include "../common/location.h"
#include "../common/ilocatable.h"
#include "../team/team.h"


enum DIRECTION { NORTH, SOUTH, EAST, WEST, NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST };
class Team; //  forward declaration
class Player : public ILocatable
{
    public:
        Player(unsigned int position_index);
        virtual ~Player();
        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void MoveUpToRight();
        void MoveUpToLeft();
        void MoveDownToRight();
        void MoveDownToLeft();
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
    protected:

    private:
        DIRECTION direction;
        static const int PLAYER_SPEED = 10;
        bool selected;
        bool kicking;
        bool recoveringBall;
        Team* team;
        unsigned int position_index;
};

#endif // PLAYER_H
