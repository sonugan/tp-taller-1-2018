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
	this->match->SetRemainingTime(this->timer->GetRemainingTime());
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
			TEAM_NUMBER goal_kick_team = this->match->GetMatchState()->GetGoalKickTeam();
			Team* team = this->match->GetTeamByNumber(goal_kick_team);
			Keeper* keeper = team->GetKeeper();
			this->match->GetBall()->GoToKeeper(keeper);
			this->match->GetMatchState()->SetPlaying();
		}
		break;
	case TIME_UP:
		if (this->match->GetMatchState()->IsReadyToChange()) {
			if(MATCH_TIME_TYPE::SECOND_TIME == this->match->GetMatchTime()) {
				// Fin del partido
				Logger::getInstance()->debug("(GameState:UpdateMatchState) Estado actual: [TIME_UP] - Actualizando a: [FINISHED]");
				Player* player;
				for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++)
				{
					player = GetMatch()->GetTeamA()->GetPlayerByPositionIndex(i);
					player->ChangeToStill();
					player->SetIsStill(true);

					player = GetMatch()->GetTeamB()->GetPlayerByPositionIndex(i);
					player->ChangeToStill();
					player->SetIsStill(true);
				}
				this->match->GetMatchState()->SetFinished();
			} else {
				Logger::getInstance()->debug("(GameState:UpdateMatchState) Estado actual: [TIME_UP] - Actualizando a: [KICKOFF]");
				// Seteo el segundo tiempo
				this->match->SetMatchTime(MATCH_TIME_TYPE::SECOND_TIME);
				this->match->GetBall()->ReturnToMiddle();

				this->match->ChangeTeamSides();

				// Vuelve a sacar el team_a (TEAM_A ES EL DE LA IZQ Y TEAM_B EL DE LA DER SIEMPRE)
				this->match->SetKickOffLocations(TEAM_NUMBER::TEAM_A);
				this->match->GetMatchState()->SetKickOff(TEAM_NUMBER::TEAM_A);
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
    	new_player_a = new Player(i, team_a);
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
    	new_player_b = new Player(i, team_b);
        ball->AddPlayerToObserve(new_player_b);
    	// Se setea de forma arbitratia que el team A sea el primero en sacar
    	new_player_b->SetInitialLocation(formation_team_b->GetKickoffLocationForPlayer(i, false));
        team_b->AddPlayer(new_player_b);
    }
    team_b->SetKeeper(keeper_b);

    this->timer = new Timer(initial_configuration->GetGameDuration());
    Pitch* pitch = new Pitch(team_a, team_b);
    this->match = new Match(pitch, team_a, team_b, ball);
    this->match->SetRemainingTime(this->timer->GetRemainingTime());
}

bool GameState::WasConnected(User* user) {
	auto it = this->users.find(user->GetUsername());
	if(it != this->users.end()) {
		return it->second == user->GetPassword();
	}
	return false;
}

void GameState::SetGoalState(TEAM_NUMBER goaler_team) {
	this->timer->Stop();
	this->match->GetMatchState()->SetGoal(goaler_team);
}
