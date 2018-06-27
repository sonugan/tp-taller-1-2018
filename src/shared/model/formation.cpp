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
        defense_areas.push_back(new Rectangle(0,0,0,0));//TODO: Arquero
        defense_areas.push_back(new Rectangle(left_goal_line, 660, top_touchline, 468));
        defense_areas.push_back(new Rectangle(left_goal_line, 660, 468, 768));
        defense_areas.push_back(new Rectangle(left_goal_line, 660, 768, bottom_touchline));
        defense_areas.push_back(new Rectangle(660, 950, top_touchline, 468));
        defense_areas.push_back(new Rectangle(660, 950, 468, 768));
        defense_areas.push_back(new Rectangle(660, 950, 768, bottom_touchline));
    	//TODO: AJUSTAR KICKOFF LOCATION PARA CADA FORMATION!
        positions.push_back(CreatePosition(new Location(260, 618, 0), new Location(260, 618, 0), new Location(260, 618, 0)));
        positions.push_back(CreatePosition(new Location(660, 318, 0), new Location(660, 318, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(660, 618, 0), new Location(660, 618, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(660, 918, 0), new Location(660, 918, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(900, 318, 0), new Location(900, 448, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(900, 618, 0), new Location(950, 610, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(900, 918, 0), new Location(900, 788, 0), new Location(360, 618, 0)));
    }
    else if (FORMATION::F_3_2_1 == this->value)
    {
        defense_areas.push_back(new Rectangle(0,0,0,0));//TODO: Arquero
        defense_areas.push_back(new Rectangle(left_goal_line, 660, top_touchline, 468));
        defense_areas.push_back(new Rectangle(left_goal_line, 660, 468, 768));
        defense_areas.push_back(new Rectangle(left_goal_line, 660, 768, bottom_touchline));
        defense_areas.push_back(new Rectangle(660, 800, top_touchline, 618));
        defense_areas.push_back(new Rectangle(800, 900, top_touchline, bottom_touchline));
        defense_areas.push_back(new Rectangle(660, 800, 618, bottom_touchline));

        positions.push_back(CreatePosition(new Location(260, 618, 0), new Location(260, 618, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(660, 318, 0), new Location(660, 318, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(660, 618, 0), new Location(660, 618, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(660, 918, 0), new Location(660, 918, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(800, 418, 0), new Location(900, 448, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(900, 618, 0), new Location(950, 610, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(800, 818, 0), new Location(900, 788, 0), new Location(360, 618, 0)));
    }
    else if (FORMATION::F_3_1_2 == this->value)
    {
        defense_areas.push_back(new Rectangle(0,0,0,0));//TODO: Arquero
        defense_areas.push_back(new Rectangle(left_goal_line, 660, top_touchline, 468));
        defense_areas.push_back(new Rectangle(left_goal_line, 660, 468, 768));
        defense_areas.push_back(new Rectangle(left_goal_line, 660, 768, bottom_touchline));
        defense_areas.push_back(new Rectangle(660, 800, top_touchline, bottom_touchline));
        defense_areas.push_back(new Rectangle(800, 900, top_touchline, 618));
        defense_areas.push_back(new Rectangle(800, 900, 618, bottom_touchline));

        positions.push_back(CreatePosition(new Location(260, 618, 0), new Location(260, 618, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(660, 318, 0), new Location(660, 318, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(660, 618, 0), new Location(660, 618, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(660, 918, 0), new Location(660, 918, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(800, 618, 0), new Location(900, 448, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(900, 418, 0), new Location(950, 610, 0), new Location(360, 618, 0)));
        positions.push_back(CreatePosition(new Location(900, 818, 0), new Location(900, 788, 0), new Location(360, 618, 0)));
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
        defense_areas.push_back(new Rectangle(0,0,0,0));//TODO: Arquero
        defense_areas.push_back(new Rectangle(1260, goal_line, top_touchline, 468));
        defense_areas.push_back(new Rectangle(1260, goal_line, 468, 768));
        defense_areas.push_back(new Rectangle(1260, goal_line, 768, bottom_touchline));
        defense_areas.push_back(new Rectangle(1020, 1260, top_touchline, 468));
        defense_areas.push_back(new Rectangle(1020, 1260, 468, 768));
        defense_areas.push_back(new Rectangle(1020, 1260, 768, bottom_touchline));
    	//TODO: AJUSTAR KICKOFF LOCATION PARA CADA FORMATION!
        positions.push_back(CreatePosition(new Location(1660, 618, 0), new Location(1660, 618, 0), new Location(1660, 618, 0)));
        positions.push_back(CreatePosition(new Location(1260, 318, 0), new Location(1260, 318, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1260, 618, 0), new Location(1260, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1260, 918, 0), new Location(1260, 918, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1020, 318, 0), new Location(1020, 518, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1020, 618, 0), new Location(1020, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1020, 918, 0), new Location(1020, 740, 0), new Location(1560, 618, 0)));
    }
    else if (FORMATION::F_3_2_1 == this->value)
    {
        defense_areas.push_back(new Rectangle(0,0,0,0));//TODO: Arquero
        defense_areas.push_back(new Rectangle(1260, goal_line, top_touchline, 468));
        defense_areas.push_back(new Rectangle(1260, goal_line, 468, 768));
        defense_areas.push_back(new Rectangle(1260, goal_line, 768, bottom_touchline));
        defense_areas.push_back(new Rectangle(1120, 1260, top_touchline, 618));
        defense_areas.push_back(new Rectangle(1020, 1120, top_touchline, bottom_touchline));
        defense_areas.push_back(new Rectangle(1120, 1260, 618, bottom_touchline));

        positions.push_back(CreatePosition(new Location(1660, 618, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1260, 318, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1260, 618, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1260, 918, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1120, 418, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1020, 618, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1120, 818, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
    }
    else if (FORMATION::F_3_1_2 == this->value)
    {
        defense_areas.push_back(new Rectangle(0,0,0,0));//TODO: Arquero
        defense_areas.push_back(new Rectangle(1260, goal_line, top_touchline, 468));
        defense_areas.push_back(new Rectangle(1260, goal_line, 468, 768));
        defense_areas.push_back(new Rectangle(1260, goal_line, 768, bottom_touchline));
        defense_areas.push_back(new Rectangle(1020, 1120, top_touchline, 618));
        defense_areas.push_back(new Rectangle(1120, 1260, top_touchline, bottom_touchline));
        defense_areas.push_back(new Rectangle(1020, 1120, 618, bottom_touchline));

        positions.push_back(CreatePosition(new Location(1660, 618, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1260, 318, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1260, 618, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1260, 918, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1020, 418, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1120, 618, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
        positions.push_back(CreatePosition(new Location(1020, 818, 0), new Location(360, 618, 0), new Location(1560, 618, 0)));
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
    return positions[player_index]->GetDefaultLocation();
}

Rectangle* Formation::GetDefenseAreaForPlayer(u_int player_index)
{
    return defense_areas[player_index];
}

Location* Formation::GetKeeperLocation() {
	return this->GetLocationForPlayer(0);
}

Location* Formation::GetKickoffLocationForPlayer(unsigned int player_index, bool is_kicker_team)
{
    return is_kicker_team ? positions[player_index]->GetKickoffLocation() : positions[player_index]->GetPassiveKickoffLocation();
}

Location* Formation::GetKeeperKickoffLocation() {
	return this->GetKickoffLocationForPlayer(0, false);
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

Position* Formation::CreatePosition(Location* default_location, Location* kickoff_location, Location* passive_kickoff_location) {
	return new Position(default_location, kickoff_location, passive_kickoff_location);
}

void Formation::ChangeSide()
{
    this->positions.clear();
    this->defense_areas.clear();
    if (this->team_number == TEAM_NUMBER::TEAM_A)
    {
        this->team_number = TEAM_NUMBER::TEAM_B;
        this->InitializePositionsTeamB();
    }
    else
    {
        this->team_number = TEAM_NUMBER::TEAM_A;
        this->InitializePositionsTeamA();
    }
}

TEAM_NUMBER Formation::GetTeamNumber()
{
    return this->team_number;
}
