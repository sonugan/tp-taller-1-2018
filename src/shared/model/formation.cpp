#include "formation.h"
#include "../logger.h"

Formation::Formation(string string_value, TEAM_NUMBER team_number) {
    if (string_value == "3-3")
    {
        this->value = F_3_3;
    } else if (string_value == "3-2-1") {
        this->value = F_3_2_1;
    } else {
        this->value = F_3_1_2;
    }

    this->team_number = team_number;

    InitializePositions();
}

Formation::Formation(FORMATION value, TEAM_NUMBER team_number) {
    this->value = value;
    this->team_number = team_number;
    InitializePositions();
}

Formation::~Formation() {
    Logger::getInstance()->debug("DESTRUYENDO FORMACION");
    for (unsigned int i = 0; i < positions.size(); i++) {
        delete positions[i];
    }
    positions.clear();
}

void Formation::InitializePositionsTeamA() {
    if (FORMATION::F_3_3 == this->value) {
        positions.push_back(new Location(360, 508, 0));
        positions.push_back(new Location(860, 208, 0));
        positions.push_back(new Location(860, 508, 0));
        positions.push_back(new Location(860, 808, 0));
        positions.push_back(new Location(1260, 208, 0));
        positions.push_back(new Location(1260, 508, 0));
        positions.push_back(new Location(1260, 808, 0));
    } else if (FORMATION::F_3_2_1 == this->value) {
        positions.push_back(new Location(360, 508, 0));
        positions.push_back(new Location(860, 208, 0));
        positions.push_back(new Location(860, 508, 0));
        positions.push_back(new Location(860, 808, 0));
        positions.push_back(new Location(1160, 258, 0));
        positions.push_back(new Location(1260, 508, 0));
        positions.push_back(new Location(1160, 758, 0));
    } else if (FORMATION::F_3_1_2 == this->value) {
        positions.push_back(new Location(360, 508, 0));
        positions.push_back(new Location(860, 208, 0));
        positions.push_back(new Location(860, 508, 0));
        positions.push_back(new Location(860, 808, 0));
        positions.push_back(new Location(1260, 258, 0));
        positions.push_back(new Location(1160, 508, 0));
        positions.push_back(new Location(1260, 758, 0));
    }
}

void Formation::InitializePositionsTeamB() {

        static const int MAX_X_LOCATION = 1920;

    if (FORMATION::F_3_3 == this->value) {
        positions.push_back(new Location(1560, 508, 0));
        positions.push_back(new Location(1060, 208, 0));
        positions.push_back(new Location(1060, 508, 0));
        positions.push_back(new Location(1060, 808, 0));
        positions.push_back(new Location(660, 208, 0));
        positions.push_back(new Location(660, 508, 0));
        positions.push_back(new Location(660, 808, 0));
    } else if (FORMATION::F_3_2_1 == this->value) {
        positions.push_back(new Location(1560, 508, 0));
        positions.push_back(new Location(1060, 208, 0));
        positions.push_back(new Location(1060, 508, 0));
        positions.push_back(new Location(1060, 808, 0));
        positions.push_back(new Location(760, 258, 0));
        positions.push_back(new Location(1260, 508, 0));
        positions.push_back(new Location(1160, 758, 0));
    } else if (FORMATION::F_3_1_2 == this->value) {
        positions.push_back(new Location(1560, 508, 0));
        positions.push_back(new Location(1060, 208, 0));
        positions.push_back(new Location(1060, 508, 0));
        positions.push_back(new Location(1060, 808, 0));
        positions.push_back(new Location(1260, 258, 0));
        positions.push_back(new Location(760, 508, 0));
        positions.push_back(new Location(660, 758, 0));
    }


}


void Formation::InitializePositions() {
    if (this->team_number == TEAM_A)
    {
        this->InitializePositionsTeamA();
    }
    else
    {
        this->InitializePositionsTeamB();
    }
}

Location* Formation::GetLocationForPlayer(unsigned int player_index) {
    return positions[player_index];
}

FORMATION Formation::GetValue() {
    return this->value;
}
