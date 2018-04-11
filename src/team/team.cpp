#include "team.h"
#include "logger.h"


Team::Team(Formation* formation, string name, string shirt) {
    this->formation = formation;
    this->name = name;
    this->shirt = shirt;
}

Team::~Team() {
    Logger::getInstance()->debug("DESTRUYENDO EQUIPO");
    delete formation;
    for (unsigned int i; i < players.size(); i++) {
        delete players[i];
    }
    players.clear();
}

std::vector<Player*> Team::GetPlayers() {
    return players;
}

void Team::SetFormation(Formation* formation) {
    Formation* old_formation = this->formation;
    this->formation = formation;
    delete old_formation;
}

Formation* Team::GetFormation() {
    return this->formation;
}

void Team::AddPlayer(Player* player) {
    if (players.size() < TEAM_SIZE) {
        players.push_back(player);
        player->SetTeam(this);
    }
}

string Team::GetName() {
    return this->name;
}

string Team::GetShirt() {
    return this->shirt;
}
