#ifndef FORMATION_H
#define FORMATION_H

#include <vector>
#include <iostream>
#include <string>
#include "location.h"
#include "../configuration/configuration.h"

class Team;

enum FORMATION { F_3_3, F_3_1_2, F_3_2_1 };

class Formation
{
public:
    Formation(FORMATION value, TEAM_NUMBER team_number);
    Formation(std::string string_value, TEAM_NUMBER team_number);
    virtual ~Formation();
    Location* GetLocationForPlayer(unsigned int player_index);
    FORMATION GetValue();

protected:

private:
    FORMATION value;
    int team_number;
    std::vector<Location*> positions;
    void InitializePositions();
    void InitializePositionsTeamA();
    void InitializePositionsTeamB();
};
#endif // FORMATION_H

