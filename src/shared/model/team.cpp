#include "team.h"
#include "../logger.h"


Team::Team(Formation* formation, string name, string shirt, TEAM_NUMBER team_number) // @suppress("Class members should be properly initialized")
{
    this->formation = formation;
    this->name = name;
    this->shirt = shirt;
    this->team_number = team_number;
    this->goals = 0;
    this->team_a_goal_line = new Location(1729, 0, 0);
    this->team_b_goal_line = new Location(185, 0, 0);
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
    delete keeper;
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

std::vector<Player*> Team::GetSelectedPlayers()
{
    std::vector<Player*> selected_players;

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        Player* player = GetPlayers()[i];

        if (player->IsSelected()) {
            selected_players.push_back(player);
        }

    }

    return selected_players;
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

void Team::SetShirt(string shirt)
{
    this->shirt = shirt;
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

void Team::SetKeeper(Keeper* keeper) {
	this->keeper = keeper;
	this->keeper->SetTeam(this);
}

Keeper* Team::GetKeeper() {
	return this->keeper;
}

string Team::GetName()
{
    return this->name;
}

string Team::GetShirt()
{
    return this->shirt;
}

//USAR SOLO DESDE EL CLIENTE
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

void Team::UpdateFormation()
{
    Player* cPlayer;
    for (unsigned int i = 0; i < (Team::TEAM_SIZE); i++)
    {
        cPlayer = this->players[i];
        cPlayer->SetLocation(cPlayer->GetDefaultLocation());
    }
}

Player* Team::GetPlayerByPositionIndex(unsigned int position_index) {
	return this->players[position_index - 1];
}

void Team::AddGoal()
{
    this->goals++;
}

int Team::GetGoals()
{
    return this->goals;
}

int Team::SetGoals(int goals)
{
    this->goals = goals;
}

Location* Team::GetTeamAGoalLine()
{
    return this->team_a_goal_line;
}

Location* Team::GetTeamBGoalLine()
{
    return this->team_b_goal_line;
}

bool Team::HasBall()
{
    Ball* ball = this->GetMatch()->GetBall();
    return !ball->IsFree() && ((ball->GetPlayer() != NULL && ball->GetPlayer()->GetTeam() == this) || (ball->GetKeeper() != NULL && ball->GetKeeper()->GetTeam() == this));
}

void Team::SetTeamNumber(TEAM_NUMBER number)
{
    this->team_number = number;
    this->formation->ChangeSide();
    for (int i = 0; i < TEAM_SIZE; i++)
    {
        this->players[i]->UpdatePlayerSide();
    }
    this->keeper->UpdateKeeperSide();
}
