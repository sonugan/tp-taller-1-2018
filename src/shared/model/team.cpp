#include "team.h"
#include "../logger.h"


Team::Team(Formation* formation, string name, string shirt, TEAM_NUMBER team_number)
{
    this->formation = formation;
    this->name = name;
    this->shirt = shirt;
    this->team_number = team_number;
}

Team::~Team()
{
    Logger::getInstance()->debug("DESTRUYENDO EQUIPO");
    delete formation;
    for (unsigned int i = 0; i < players.size(); i++)
    {
        delete players[i];
    }
    players.clear();
}

std::vector<Player*> Team::GetPlayers()
{
    return players;
}

std::vector<Player*> Team::GetAvailablePlayers()
{
    std::vector<Player*> available_players;

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        Player* player = GetPlayers()[i];

        if (!player->IsSelected()) {
            available_players.push_back(player);
        }

    }

    return available_players;
}

void Team::SetFormation(Formation* formation)
{
    Formation* old_formation = this->formation;
    this->formation = formation;
    delete old_formation;
}

void Team::SetMatch(Match* match)
{
    this->match = match;
}

Formation* Team::GetFormation()
{
    return this->formation;
}

Match* Team::GetMatch()
{
    return this->match;
}

void Team::AddPlayer(Player* player)
{
    if (players.size() < TEAM_SIZE)
    {
        players.push_back(player);
        player->SetTeam(this);
    }
}

string Team::GetName()
{
    return this->name;
}

string Team::GetShirt()
{
    return this->shirt;
}

Player* Team::GetSelectedPlayer()
{
    for (unsigned int i = 0; i < (Team::TEAM_SIZE); i++)
    {
        Player* player = GetPlayers()[i];
        if (player->IsSelected())
        {
            return player;
        }
    }
    return NULL;
}

TEAM_NUMBER Team::GetTeamNumber()
{
    return this->team_number;
}
