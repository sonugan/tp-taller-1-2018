#ifndef END_LINE_ZONE_H
#define END_LINE_ZONE_H

#include "ipitch-zone.h"

class Team;
class Ball;
class EndLineZone : public iPitchZone
{
    public:
        EndLineZone(Team* team, Location* top_left_corner, Location* bottom_right_corner);
        ~EndLineZone();
        bool IsTouching(Ball* ball);
        void SetTeam(Team* team);
        Team* GetTeam();
    protected:
        Team* team;
    private:
};

#endif // END_LINE_ZONE_H
