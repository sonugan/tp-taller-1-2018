#include "formation.h"
#include "logger.h"

Formation::Formation(FORMATION value)
{
    this->value = value;
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

Formation::~Formation() {
    Logger::getInstance()->debug("DESTRUYENDO FORMACION");
    for (unsigned int i; i < positions.size(); i++) {
        delete positions[i];
    }
    positions.clear();
}

Location* Formation::GetLocationForPlayer(unsigned int player_index) {
    return positions[player_index];
}

FORMATION Formation::GetValue() {
    return this->value;
}
