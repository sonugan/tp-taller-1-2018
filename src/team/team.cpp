#include "team.h"
#include "logger.h"


Team::Team(Formation* formation) {
    this->formation = formation;
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
    this->formation = formation;
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
