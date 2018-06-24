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
	MATCH_STATE_TYPE current_state_type = this->match->GetMatchState()->GetType();
	switch (current_state_type)
	{
	case PLAYING:
		if(this->timer->IsTimeUp()) {
			Logger::getInstance()->debug("(GameState:UpdateMatchState) Estado actual: [PLAYING] - Actualizando a: [TIMEUP]");
			if(MATCH_TIME_TYPE::FIRST_TIME == this->match->GetMatchTime()) {
				this->timer->Stop();
			}
			this->match->GetMatchState()->SetTimeup();
		}
		break;
	case GOAL:
	{
		this->timer->Stop();
		TEAM_NUMBER kicker_team = TEAM_NUMBER::TEAM_A == this->GetMatch()->GetMatchState()->GetGoalScorerTeam() ? TEAM_NUMBER::TEAM_B : TEAM_NUMBER::TEAM_A;
		if (this->match->GetMatchState()->IsReadyToChange()) {
			Logger::getInstance()->debug("(GameState:UpdateMatchState) Estado actual: [GOAL] - Actualizando a: [KICKOFF]");
			this->match->SetKickOffLocations(kicker_team);
			this->match->GetBall()->ReturnToMiddle();
			this->match->GetMatchState()->SetKickOff(kicker_team);
		}
		break;
	}
	case KICKOFF:
		if (this->match->GetMatchState()->IsReadyToChange()) {
			Logger::getInstance()->debug("(GameState:UpdateMatchState) Estado actual: [KICKOFF] - Actualizando a: [PLAYING]");
			if(MATCH_STATE_TYPE::TIME_UP == this->match->GetMatchState()->GetPreviousType()) {
				this->timer->Restart();
			}
			this->match->GetMatchState()->SetPlaying();
			this->timer->Start();
		}
		break;
	case GOAL_KICK:
		if (this->match->GetMatchState()->IsReadyToChange()) {
			Logger::getInstance()->debug("(GameState:UpdateMatchState) Estado actual: [GOAL_KICK] - Actualizando a: [PLAYING]");
			Keeper* keeper = this->match->GetTeamByNumber(this->match->GetMatchState()->GetGoalKickTeam())->GetKeeper();
			this->match->GetBall()->GoToKeeper(keeper);
			this->match->GetMatchState()->SetPlaying();
		}
		break;
	case TIME_UP:
		if (this->match->GetMatchState()->IsReadyToChange()) {
			if(MATCH_TIME_TYPE::SECOND_TIME == this->match->GetMatchTime()) {
				// Fin del partido
				Logger::getInstance()->debug("(GameState:UpdateMatchState) Estado actual: [TIME_UP] - Actualizando a: [FINISHED]");
				for (unsigned int i = 1; i < Team::TEAM_SIZE; i++)
				{
					Player* player_a = GetMatch()->GetTeamA()->GetPlayerByPositionIndex(i);
					player_a->ChangeToStill();
					player_a->SetIsStill(true);
					
					Player* player_b = GetMatch()->GetTeamB()->GetPlayerByPositionIndex(i);
					player_b->ChangeToStill();
					player_b->SetIsStill(true);
				}
				this->match->GetMatchState()->SetFinished();
			} else {
				Logger::getInstance()->debug("(GameState:UpdateMatchState) Estado actual: [TIME_UP] - Actualizando a: [KICKOFF]");
				// Seteo el segundo tiempo
				this->match->SetMatchTime(MATCH_TIME_TYPE::SECOND_TIME);
				this->match->GetBall()->ReturnToMiddle();
				// segundo tiempo, saca el team B. esto es arbitrario.
				this->match->SetKickOffLocations(TEAM_NUMBER::TEAM_B);
				this->match->GetMatchState()->SetKickOff(TEAM_NUMBER::TEAM_B);
			}
		}
		break;
	default:
		break;
	}

}

void GameState::Start() {
	this->timer->Start();
}

/* Private methods */
void GameState::CreateModel(Configuration* initial_configuration)
{
    Logger::getInstance()->debug("(GameState:CreateModel) CREANDO EL MODELO");

    Ball* ball = new Ball();

    Formation* formation_team_a = new Formation(initial_configuration->GetFormation(), TEAM_NUMBER::TEAM_A);
    Team* team_a = new Team(formation_team_a, initial_configuration->GetTeamName(), initial_configuration->GetShirt(), TEAM_NUMBER::TEAM_A);
    Keeper* keeper_a = new Keeper();
    Player* new_player_a;
    for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++) {
    	new_player_a = new Player(i,TEAM_NUMBER::TEAM_A);
        ball->AddPlayerToObserve(new_player_a);
    	// Se setea de forma arbitratia que el team A sea el primero en sacar
    	new_player_a->SetInitialLocation(formation_team_a->GetKickoffLocationForPlayer(i, true));
        team_a->AddPlayer(new_player_a);
    }
    team_a->SetKeeper(keeper_a);

    Formation* formation_team_b = new Formation(initial_configuration->GetFormation(), TEAM_NUMBER::TEAM_B);
    Team* team_b = new Team(formation_team_b, "team_b", "away", TEAM_NUMBER::TEAM_B); // TODO: TRAER NOMBRE DEL TEAM B Y CAMISETA DE CONFIG
    Keeper* keeper_b = new Keeper();
    Player* new_player_b;
    for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++) {
    	new_player_b = new Player(i,TEAM_NUMBER::TEAM_B);
        ball->AddPlayerToObserve(new_player_b);
    	// Se setea de forma arbitratia que el team A sea el primero en sacar
    	new_player_b->SetInitialLocation(formation_team_b->GetKickoffLocationForPlayer(i, false));
        team_b->AddPlayer(new_player_b);
    }
    team_b->SetKeeper(keeper_b);

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
