#include "game-state.h"

#include "../../shared/logger.h"
#include "../../shared/model/pitch.h"
#include "../../shared/model/formation.h"
#include "../../shared/model/team.h"
#include "../../shared/model/player.h"
#include "../../shared/model/ball.h"

GameState::GameState(Configuration* initial_configuration)
{
    this->CreateModel(initial_configuration);
}

GameState::~GameState()
{
    delete this->match;
}

Match* GameState::GetMatch()
{
    return this->match;
}

void GameState::AddUser(string username, string password)
{
	this->users[username] = password;
}

void GameState::UpdateMatchState() {
	this->match->SetRemainingTime(this->timer->GetRemainingMinutes());
	if(this->timer->IsTimeUp()) {
		if(MATCH_TIME_TYPE::FIRST_TIME == this->match->GetMatchTime()) {
			this->match->SetMatchTime(MATCH_TIME_TYPE::SECOND_TIME);
			this->timer->Restart();
		}
	}
}

void GameState::Start() {
	this->timer->Start();
}

/* Private methods */
void GameState::CreateModel(Configuration* initial_configuration)
{
    Logger::getInstance()->debug("CREANDO EL MODELO");

    Formation* formation_team_a = new Formation(initial_configuration->GetFormation(), TEAM_NUMBER::TEAM_A);
    Team* team_a = new Team(formation_team_a, initial_configuration->GetTeamName(), initial_configuration->GetShirt(), TEAM_NUMBER::TEAM_A);
    Keeper* keeper_a = new Keeper();
    for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++) {
        team_a->AddPlayer(new Player(i,TEAM_NUMBER::TEAM_A));
    }
    team_a->SetKeeper(keeper_a);

    Formation* formation_team_b = new Formation(initial_configuration->GetFormation(), TEAM_NUMBER::TEAM_B);
    Team* team_b = new Team(formation_team_b, "team_b", "away", TEAM_NUMBER::TEAM_B); // TODO: TRAER NOMBRE DEL TEAM B Y CAMISETA DE CONFIG
    Keeper* keeper_b = new Keeper();
    for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++) {
        team_b->AddPlayer(new Player(i, TEAM_NUMBER::TEAM_B));
    }
    team_b->SetKeeper(keeper_b);

    Ball* ball = new Ball();

    this->timer = new Timer(initial_configuration->GetGameDuration());
    Pitch* pitch = new Pitch(team_a, team_b);
    this->match = new Match(pitch, team_a, team_b, ball);
    this->match->SetRemainingTime(this->timer->GetRemainingMinutes());
}

bool GameState::WasConnected(User* user) {
	auto it = this->users.find(user->GetUsername());
	if(it != this->users.end()) {
		return it->second == user->GetPassword();
	}
	return false;
}


