#include "formation.h"
#include "../logger.h"

Formation::Formation(string string_value, TEAM_NUMBER team_number)
{
    if (string_value == "3-3")
    {
        this->value = F_3_3;
    }
    else if (string_value == "3-2-1")
    {
        this->value = F_3_2_1;
    }
    else
    {
        this->value = F_3_1_2;
    }

    this->team_number = team_number;

    InitializePositions();
}

Formation::Formation(FORMATION value, TEAM_NUMBER team_number)
{
    this->value = value;
    this->team_number = team_number;
    InitializePositions();
}

Formation::~Formation()
{
    Logger::getInstance()->debug("DESTRUYENDO FORMACION");
    for (unsigned int i = 0; i < positions.size(); i++)
    {
        delete positions[i];
    }
    positions.clear();
}

void Formation::InitializePositionsTeamA()
{

    // MITAD DE CANCHA 960, 540, 0

    if (FORMATION::F_3_3 == this->value)
    {
        positions.push_back(new Location(360, 540, 0));
        positions.push_back(new Location(660, 240, 0));
        positions.push_back(new Location(660, 540, 0));
        positions.push_back(new Location(660, 840, 0));
        positions.push_back(new Location(900, 240, 0));
        positions.push_back(new Location(900, 540, 0));
        positions.push_back(new Location(900, 840, 0));
    }
    else if (FORMATION::F_3_2_1 == this->value)
    {
        positions.push_back(new Location(360, 540, 0));
        positions.push_back(new Location(660, 240, 0));
        positions.push_back(new Location(660, 540, 0));
        positions.push_back(new Location(660, 840, 0));
        positions.push_back(new Location(800, 240, 0));
        positions.push_back(new Location(900, 540, 0));
        positions.push_back(new Location(800, 740, 0));
    }
    else if (FORMATION::F_3_1_2 == this->value)
    {
        positions.push_back(new Location(360, 540, 0));
        positions.push_back(new Location(660, 240, 0));
        positions.push_back(new Location(660, 540, 0));
        positions.push_back(new Location(660, 840, 0));
        positions.push_back(new Location(800, 240, 0));
        positions.push_back(new Location(900, 540, 0));
        positions.push_back(new Location(800, 740, 0));
    }
}

void Formation::InitializePositionsTeamB()
{

    // MITAD DE CANCHA 960, 540, 0

    if (FORMATION::F_3_3 == this->value)
    {
        positions.push_back(new Location(1560, 540, 0));
        positions.push_back(new Location(1260, 240, 0));
        positions.push_back(new Location(1260, 540, 0));
        positions.push_back(new Location(1260, 840, 0));
        positions.push_back(new Location(1020, 240, 0));
        positions.push_back(new Location(1020, 540, 0));
        positions.push_back(new Location(1020, 840, 0));
    }
    else if (FORMATION::F_3_2_1 == this->value)
    {
        positions.push_back(new Location(1560, 540, 0));
        positions.push_back(new Location(1260, 240, 0));
        positions.push_back(new Location(1260, 540, 0));
        positions.push_back(new Location(1260, 840, 0));
        positions.push_back(new Location(1120, 240, 0));
        positions.push_back(new Location(1020, 540, 0));
        positions.push_back(new Location(1120, 740, 0));
    }
    else if (FORMATION::F_3_1_2 == this->value)
    {
        positions.push_back(new Location(1560, 540, 0));
        positions.push_back(new Location(1260, 240, 0));
        positions.push_back(new Location(1260, 540, 0));
        positions.push_back(new Location(1260, 840, 0));
        positions.push_back(new Location(1120, 240, 0));
        positions.push_back(new Location(1020, 540, 0));
        positions.push_back(new Location(1120, 740, 0));
    }

}

void Formation::InitializePositions()
{
    if (this->team_number == TEAM_NUMBER::TEAM_A)
    {
        this->InitializePositionsTeamA();
    }
    else
    {
        this->InitializePositionsTeamB();
    }
}

Location* Formation::GetLocationForPlayer(unsigned int player_index)
{
    return positions[player_index];
}

FORMATION Formation::GetValue()
{
    return this->value;
}
