#ifndef MATCH_H
#define MATCH_H

#include "team.h"
#include "pitch.h"

class Match
{
    public:
        Match(Pitch* pitch, Team* team_a, Team* team_b);
        virtual ~Match();
        Team* GetTeamA();
        Team* GetTeamB();
        Pitch* GetPitch();

    private:
        Team* team_a;
        Team* team_b;
        Pitch* pitch;
};

#endif // MATCH_H
