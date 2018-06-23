#ifndef FORMATION_H
#define FORMATION_H

#include <vector>
#include <iostream>
#include <string>
#include "location.h"
#include "../configuration/configuration.h"
#include "team.h"
#include "../collision/rectangle.h"

class Team;

enum FORMATION { F_3_3 = 1, F_3_1_2 = 2, F_3_2_1 = 3 };

class Formation
{
public:
    Formation(FORMATION value, TEAM_NUMBER team_number);
    Formation(std::string string_value, TEAM_NUMBER team_number);
    virtual ~Formation();
    Location* GetLocationForPlayer(unsigned int player_index);
    Location* GetKeeperLocation();
    FORMATION GetValue();
    void ChangeFormation(string formation);
    bool ChangedByUser();
    Rectangle* GetDefenseAreaForPlayer(u_int player_index);
protected:
    void SetValueFromStringFormation(string string_value);

private:
    FORMATION value;
    TEAM_NUMBER team_number;
    std::vector<Location*> positions;
    std::vector<Rectangle*> defense_areas;
    bool changed_by_user;
    void InitializePositions();
    void InitializePositionsTeamA();
    void InitializePositionsTeamB();
    void InitializeDefenseAreas();
};
#endif // FORMATION_H
