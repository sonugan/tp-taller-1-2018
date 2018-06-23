#include "formation.h"
#include "../logger.h"

Formation::Formation(string string_value, TEAM_NUMBER team_number)
{
    this->SetValueFromStringFormation(string_value);

    this->team_number = team_number;

    this->changed_by_user = false;

    InitializePositions();
}

Formation::Formation(FORMATION value, TEAM_NUMBER team_number)
{
    this->value = value;
    this->team_number = team_number;
    this->changed_by_user = false;
    InitializePositions();
}

Formation::~Formation()
{
    //Logger::getInstance()->debug("DESTRUYENDO FORMACION");
    for (unsigned int i = 0; i < positions.size(); i++)
    {
        delete positions[i];
    }
    positions.clear();
}

void Formation::InitializePositionsTeamA()
{

    // MITAD DE CANCHA 960, 618, 0
    int top_touchline = 50;
    int bottom_touchline = 1060 - 50;
    int left_goal_line = 180;
    if (FORMATION::F_3_3 == this->value)
    {
        positions.push_back(new Location(260, 618, 0));
        defense_areas.push_back(new Rectangle(new Location(0,0,0), bottom_touchline, 360));//TODO: Arquero
        positions.push_back(new Location(660, 318, 0));
        defense_areas.push_back(new Rectangle(new Location(left_goal_line, top_touchline, 0), 440, 660 - left_goal_line));
        positions.push_back(new Location(660, 618, 0));
        defense_areas.push_back(new Rectangle(new Location(left_goal_line, 440, 0), 840 - 440, 660 - left_goal_line));
        positions.push_back(new Location(660, 918, 0));
        defense_areas.push_back(new Rectangle(new Location(left_goal_line, 840,0), bottom_touchline - (840 - 440), 660 - left_goal_line));
        positions.push_back(new Location(900, 318, 0));
        defense_areas.push_back(new Rectangle(new Location(660, 0, 0), 440, 900 - 660));
        positions.push_back(new Location(900, 618, 0));
        defense_areas.push_back(new Rectangle(new Location(660, 440,  0), 840 - 440, 900 - 660));
        positions.push_back(new Location(900, 918, 0));
        defense_areas.push_back(new Rectangle(new Location(660, 840, 0), bottom_touchline - (840 - 440), 900 - 660));
    }
    else if (FORMATION::F_3_2_1 == this->value)
    {
        positions.push_back(new Location(260, 618, 0));
        positions.push_back(new Location(660, 318, 0));
        positions.push_back(new Location(660, 618, 0));
        positions.push_back(new Location(660, 918, 0));
        positions.push_back(new Location(800, 418, 0));
        positions.push_back(new Location(900, 618, 0));
        positions.push_back(new Location(800, 818, 0));
    }
    else if (FORMATION::F_3_1_2 == this->value)
    {
        positions.push_back(new Location(260, 618, 0));
        positions.push_back(new Location(660, 318, 0));
        positions.push_back(new Location(660, 618, 0));
        positions.push_back(new Location(660, 918, 0));
        positions.push_back(new Location(800, 618, 0));
        positions.push_back(new Location(900, 418, 0));
        positions.push_back(new Location(900, 818, 0));
    }
}

void Formation::InitializePositionsTeamB()
{

    // MITAD DE CANCHA 960, 618, 0
    int top_touchline = 50;
    int bottom_touchline = 1060 - 50;
    int goal_line = 1740;
    if (FORMATION::F_3_3 == this->value)
    {
        positions.push_back(new Location(1660, 618, 0));
        defense_areas.push_back(new Rectangle(new Location(0,0,0), bottom_touchline, 360));//TODO: Arquero
        positions.push_back(new Location(1260, 318, 0));
        defense_areas.push_back(new Rectangle(new Location(1260, top_touchline, 0), 440, goal_line - 1260));
        positions.push_back(new Location(1260, 618, 0));
        defense_areas.push_back(new Rectangle(new Location(1260, 440, 0), 840 - 440, goal_line - 1260));
        positions.push_back(new Location(1260, 918, 0));
        defense_areas.push_back(new Rectangle(new Location(1260, 840,0), bottom_touchline - (840 - 440), goal_line - 1260));
        positions.push_back(new Location(1020, 318, 0));
        defense_areas.push_back(new Rectangle(new Location(1020, 0, 0), 440, 1260 - 1020));
        positions.push_back(new Location(1020, 618, 0));
        defense_areas.push_back(new Rectangle(new Location(1020, 440,  0), 840 - 440, 1260 - 1020));
        positions.push_back(new Location(1020, 918, 0));
        defense_areas.push_back(new Rectangle(new Location(1020, 840, 0), bottom_touchline - (840 - 440), 1260 - 1020));
    }
    else if (FORMATION::F_3_2_1 == this->value)
    {
        positions.push_back(new Location(1660, 618, 0));
        positions.push_back(new Location(1260, 318, 0));
        positions.push_back(new Location(1260, 618, 0));
        positions.push_back(new Location(1260, 918, 0));
        positions.push_back(new Location(1120, 418, 0));
        positions.push_back(new Location(1020, 618, 0));
        positions.push_back(new Location(1120, 818, 0));
    }
    else if (FORMATION::F_3_1_2 == this->value)
    {
        positions.push_back(new Location(1660, 618, 0));
        positions.push_back(new Location(1260, 318, 0));
        positions.push_back(new Location(1260, 618, 0));
        positions.push_back(new Location(1260, 918, 0));
        positions.push_back(new Location(1020, 418, 0));
        positions.push_back(new Location(1120, 618, 0));
        positions.push_back(new Location(1020, 818, 0));
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

Rectangle* Formation::GetDefenseAreaForPlayer(u_int player_index)
{
    return defense_areas[player_index];
}

Location* Formation::GetKeeperLocation() {
	return this->GetLocationForPlayer(0);
}

FORMATION Formation::GetValue()
{
    return this->value;
}

void Formation::ChangeFormation(string formation) {
    this->changed_by_user = true;
    this->SetValueFromStringFormation(formation);
    this->positions.clear();
    this->InitializePositions();
}

void Formation::SetValueFromStringFormation(string string_value) {
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
}

bool Formation::ChangedByUser() {
    return this->changed_by_user;
}
