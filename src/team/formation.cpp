#include "formation.h"
#include "logger.h"

Formation::Formation(FORMATION value)
{
    this->value = value;
    if (FORMATION::F_3_3 == this->value) {
        positions.push_back(new Location(360, 340, 0));
        positions.push_back(new Location(660, 140, 0));
        positions.push_back(new Location(660, 340, 0));
        positions.push_back(new Location(660, 540, 0));
        positions.push_back(new Location(960, 140, 0));
        positions.push_back(new Location(960, 340, 0));
        positions.push_back(new Location(960, 540, 0));
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
