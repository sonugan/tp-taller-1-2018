#include "team.h"
#include "../logger.h"


Team::Team(Formation* formation, string name, string shirt) {
    this->formation = formation;
    this->name = name;
    this->shirt = shirt;
}

Team::~Team() {
    Logger::getInstance()->debug("DESTRUYENDO EQUIPO");
    delete formation;
    for (unsigned int i = 0; i < players.size(); i++) {
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

void Team::SetMatch(Match* match) {
    this->match = match;
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

Player* Team::GetSelectedPlayer() {
    for (unsigned int i = 0; i < (Team::TEAM_SIZE); i++) {
        Player* player = GetPlayers()[i];
        if (player->IsSelected()) {
            return player;
        }
    }
    return NULL;
}
