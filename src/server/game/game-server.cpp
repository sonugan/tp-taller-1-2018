#include "game-server.h"

#include "../../shared/logger.h"
#include "non-existen-user-exception.h"

GameServer::GameServer(Configuration* initial_configuration) {
	this->game_state = new GameState(initial_configuration);
	this->session_manager = new SessionManager(initial_configuration->GetCredentials(), initial_configuration->GetMaxPlayers());
}

GameServer::~GameServer() {
	delete this->game_state;
	delete this->session_manager;
}

GameState* GameServer::GetGameState() {
	return this->game_state;
}

Player* GameServer::GetUserSelectedPlayer(std::vector<Player*> available_players) {
	// TIENE QUE SER ALGUNO DE LOS DELANTEROS = POSICIONES 4, 5 O 6

	for (unsigned int i = 0; i < available_players.size(); i++) {
		Player* player = available_players[i];

		if (player->GetPositionIndex() >= 4 && player->GetPositionIndex() <= 6) {
			return player;
		}

	}

	return NULL;
}

void GameServer::DoLogin(ClientSocket* client, LoginRequest* login_request) {
	User* authenticated_user = this->session_manager->Authenticate(client, login_request);

	bool was_not_connected = !this->game_state->WasConnected(authenticated_user);
	if (this->is_running && was_not_connected) {
		throw NonExistentUserException("Error. El usuario no puede ser reconectado a la partida.");
	}
	// SETEO EL JUGADOR ACTIVO

	Team* selected_team = this->game_state->GetMatch()->GetTeamB();

	if (authenticated_user->GetSelectedTeam() == TEAM_NUMBER::TEAM_A) {
		selected_team = this->game_state->GetMatch()->GetTeamA();
	}

	Player* selected_player = this->GetUserSelectedPlayer(selected_team->GetAvailablePlayers());

	selected_player->SetPlayerColor(authenticated_user->GetUserColor());
	authenticated_user->SetSelectedPlayer(selected_player);

}

void GameServer::DoQuit(ClientSocket* client) {
	this->DisconnectClient(client);
}

std::string GameServer::DoRecoverBall(RecoverBallRequest* recover_ball_request, int socket_id) {
	User* user = this->session_manager->GetUserBySocketID(socket_id);
	user->GetSelectedPlayer()->RecoverBall();
	return this->game_state->GetMatch()->Serialize();
}

std::string GameServer::DoKick(KickBallRequest* kick_request, int socket_id) {
	User* user = this->session_manager->GetUserBySocketID(socket_id);
	unsigned int power = kick_request->GetPower();
	user->GetSelectedPlayer()->KickBall(power);
	return this->game_state->GetMatch()->Serialize();
}

std::string GameServer::DoLongPass(LongPassRequest* long_pass_request, int socket_id) {
	User* user = this->session_manager->GetUserBySocketID(socket_id);
	unsigned int power = long_pass_request->GetPower();
	user->GetSelectedPlayer()->LongPass(power, TRAJECTORY_TYPE::UPWARDS); //Mirar esto!!!
	return this->game_state->GetMatch()->Serialize();
}

Message* GameServer::DoPassBall(ClientSocket* client, PassBallRequest* pass_ball_request) {
	Logger::getInstance()->debug("(GameServer::DoPassBall) REQUEST DE PASE RECIBIDO");
	User* user = this->session_manager->GetUserBySocketID(client->socket_id);
	user->GetSelectedPlayer()->PassBall();
	return new Message(this->game_state->GetMatch()->Serialize());
}

std::string GameServer::DoMove(MoveRequest* move_request, int socket_id) {
	User* user = this->session_manager->GetUserBySocketID(socket_id);
	DIRECTION direction = move_request->GetDirection();
	bool running = move_request->IsRunning();
	if (direction == DIRECTION::NORTH) {
		user->GetSelectedPlayer()->MoveUp(running);
	} else if (direction == DIRECTION::SOUTH) {
		user->GetSelectedPlayer()->MoveDown(running);
	} else if (direction == DIRECTION::EAST) {
		user->GetSelectedPlayer()->MoveRight(running);
	} else if (direction == DIRECTION::WEST) {
		user->GetSelectedPlayer()->MoveLeft(running);
	} else if (direction == DIRECTION::NORTHEAST) {
		user->GetSelectedPlayer()->MoveUpToRight(running);
	} else if (direction == DIRECTION::NORTHWEST) {
		user->GetSelectedPlayer()->MoveUpToLeft(running);
	} else if (direction == DIRECTION::SOUTHEAST) {
		user->GetSelectedPlayer()->MoveDownToRight(running);
	} else if (direction == DIRECTION::SOUTHWEST) {
		user->GetSelectedPlayer()->MoveDownToLeft(running);
	}

	return this->game_state->GetMatch()->Serialize();

}

string GameServer::ChangePlayer(ChangePlayerRequest* change_player_request, int socket_id) {
	User* user = this->session_manager->GetUserBySocketID(socket_id);
	Player* last_selected_player = user->GetSelectedPlayer();

	Player* next_player = NULL;
	Team* team = user->GetSelectedPlayer()->GetTeam();

	unsigned int new_selected_player_position_index = user->GetSelectedPlayer()->GetPositionIndex();

	for (unsigned int i = 0; i < (Team::TEAM_SIZE - 1); i++) {

		if (new_selected_player_position_index == Team::TEAM_SIZE) {
			new_selected_player_position_index = 1;
		} else {
			new_selected_player_position_index++;
		}

		Player* possible_player = team->GetPlayerByPositionIndex(new_selected_player_position_index);
		if (!possible_player->IsSelected()) {
			next_player = possible_player;
			break;
		}
	}

	last_selected_player->SetPlayerColor(USER_COLOR::NO_COLOR);
	next_player->SetPlayerColor(user->GetUserColor());
	user->SetSelectedPlayer(next_player);

	return this->game_state->GetMatch()->Serialize();
}

bool GameServer::IsReadyToStart() {
	if (this->session_manager->IsReadyToStart()) {
		return this->TeamsHaveFormation();
	}

	return false;
}

bool GameServer::TeamsHaveFormation() {
	//Me fijo si los equipos tienen formacion definida por algun usuario en caso que el equipo tenga jugadores no NPC
	bool team_a_has_formation = true, team_b_has_formation = true;
	map<string, User*> users = this->session_manager->GetAuthenticatedUsers();
	Team* team;
	Team* teamA = this->game_state->GetMatch()->GetTeamA();
	for (const auto& u : users) {
		team = u.second->GetSelectedPlayer()->GetTeam();
		if (team == teamA) {
			team_a_has_formation = team->GetFormation()->ChangedByUser();
		} else {
			team_b_has_formation = team->GetFormation()->ChangedByUser();
		}
	}

	Logger::getInstance()->debug("(GameServer::TeamsHaveFormation) Todavia hay equipos con usuarios que no tienen la formacion elegida por su capitan");
	return (team_a_has_formation && team_b_has_formation);
}

void GameServer::StartGame() {
	Logger::getInstance()->info("(GameServer:StartGame) Comenzando el juego.");
	this->is_running = true;
	/*
	 * Agrego registro de usuarios logueados al gamestate para casos de reconexión
	 * */
	auto it = this->session_manager->GetAuthenticatedUsers().begin();
	while (it != this->session_manager->GetAuthenticatedUsers().end()) {
		this->game_state->AddUser(it->second->GetUsername(), it->second->GetPassword());
		it++;
	}

	this->game_state->Start();
}

void GameServer::RunArtificialIntelligence() {
	this->CatchBall();
	this->MoveBall();
	this->MovePlayersToDefaultPositions();
	this->DetectBallTouches();
}

void GameServer::DetectBallTouches()
{
    Ball* ball = this->game_state->GetMatch()->GetBall();

    this->BounceBallOnThrowIn(ball);
    this->BounceBallOnGoalPost(ball);
    this->ReturnBallToKeeperOnGoalKick(ball);
    this->DetectGoals(ball);
}

void GameServer::BounceBallOnGoalPost(Ball* ball)
{
    if (!ball->IsFree())
    {
        return;
    }

    if (this->game_state->GetMatch()->GetPitch()->BallTouchingGoalPost(ball))
    {
        Logger::getInstance()->debug("(GameServer::BounceBallOnGoalPost) Rebotando pelota en un palo");
        ball->BounceOnGoalPost();
    }
}

void GameServer::ReturnBallToKeeperOnGoalKick(Ball* ball)
{
    Team* goal_keeper_team = this->game_state->GetMatch()->GetPitch()->BallTouchingEndLineZone(ball);
    if (goal_keeper_team != NULL)
    {
        Logger::getInstance()->info("[SAQUE DE ARCO] La pelota se fue por la linea de fondo y es saque de arco para el equipo " + goal_keeper_team->GetName());
        ///Le doy la pelota al arquero del equipo
        ball->GoToKeeper(goal_keeper_team->GetKeeper());
    }
}

void GameServer::BounceBallOnThrowIn(Ball* ball)
{
    if (!ball->IsFree())
    {
        return;
    }

    if (this->game_state->GetMatch()->GetPitch()->BallTouchingThrowIn(ball))
    {
        Logger::getInstance()->debug("(GameServer::BounceBallOnThrowIn) Rebotando pelota en los laterales");
        ball->BounceOnThrowIn();
    }
}

void GameServer::DetectGoals(Ball* ball)
{
	///Equipo donde hicieron el gol
	Team* scoring_on_goal_team = this->game_state->GetMatch()->GetPitch()->ScoringAtSomeGoal(ball);

	if (scoring_on_goal_team != NULL)
	{
		///Equipo que hizo el gol
		Team* goaler_team = this->game_state->GetMatch()->GetOppositeTeam(scoring_on_goal_team);
		///Equipo del jugador que hizo el gol
		Team* goal_scorer_team = ball->GetLastOwnerTeam();

		if (ball->GetLastOwnerColor() != USER_COLOR::NO_COLOR) {
			Logger::getInstance()->info(
					"[GOOL] El usuario " + this->session_manager->GetUserByColor(ball->GetLastOwnerColor())->GetUsername() + " convirtio un gol para el equipo "
							+ goaler_team->GetName());
		} else {
			Logger::getInstance()->info(
					"[GOOL] La IA del equipo " + ball->GetLastOwnerTeam()->GetName() + " convirtio un gol para el equipo " + goaler_team->GetName());
		}

		ball->ReturnToMiddle();
		if (scoring_on_goal_team != goal_scorer_team) {
			//Si el equipo del que hace el gol es distinto del equipo del arco en el que se hace el gol => suma goles el equipo del goleador (el que hizo el gol)
			goal_scorer_team->AddGoal();
		} else {
			//Si no pasa lo anterior sumo goles al equipo contrario
			goaler_team->AddGoal();
		}

		Team* team_a = this->game_state->GetMatch()->GetTeamA();
		Team* team_b = this->game_state->GetMatch()->GetTeamB();
		Logger::getInstance()->info(
				"[RESULTADO PARCIAL] " + team_a->GetName() + " " + to_string(team_a->GetGoals()) + " - " + to_string(team_b->GetGoals()) + " "
						+ team_b->GetName());
	}
}

void GameServer::CatchBall() {
	if (this->GetGameState()->GetMatch()->GetBall()->LastFreedDelayPassed()) {
		for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++) {
			Player* player_a = this->GetGameState()->GetMatch()->GetTeamA()->GetPlayerByPositionIndex(i);
			MakePlayerCatchBall(player_a);
			Player* player_b = this->GetGameState()->GetMatch()->GetTeamB()->GetPlayerByPositionIndex(i);
			MakePlayerCatchBall(player_b);
		}
	}

}

void GameServer::MakePlayerCatchBall(Player* player) {
	if (!player->HasBall()) {
		Ball* ball = player->GetTeam()->GetMatch()->GetBall();
		bool collides = ball->GetCircle()->ExistsCollision3d(player->GetCircle());
		if (ball->IsFree() && collides) {
			Trajectory* trajectory = new Trajectory(player);
            ball->SetTrajectory(trajectory);
			if (USER_COLOR::NO_COLOR == player->GetPlayerColor()) {
				/*
				 Si el jugador que agarra la pelota no estaba seleccionado,
				 es seleccionado por el jugador del mismo equipo que estaba más cerca.
				 */
				std::vector<Player*> selected_players = player->GetTeam()->GetSelectedPlayers();
				Player* closest_selected_player = NULL;
				unsigned int closest_selected_player_distance_to_ball = 99999;

				for (unsigned int i = 0; i < selected_players.size(); i++) {
					Player* selected_player = selected_players[i];
					unsigned int distance = selected_player->GetLocation()->Distance(ball->GetLocation());
					if (distance <= closest_selected_player_distance_to_ball) {
						closest_selected_player = selected_player;
						closest_selected_player_distance_to_ball = distance;
					}
				}

				if (closest_selected_player != NULL) {
					player->SetPlayerColor(closest_selected_player->GetPlayerColor());
					User* user = this->session_manager->GetUserByColor(closest_selected_player->GetPlayerColor());
					user->SetSelectedPlayer(player);
					closest_selected_player->SetPlayerColor(USER_COLOR::NO_COLOR);
				}
			}

			//Si el ultimo poseedor de la pelota era de distinto equipo que el que agarra la pelota => es un "recupero de pelota"
			if (ball->GetLastOwnerTeam() != NULL && ball->GetLastOwnerTeam() != player->GetTeam()) {
				User* user = this->session_manager->GetUserByColor(player->GetPlayerColor());
				if (user != NULL) {
					Logger::getInstance()->info(
							"[RECUPERO DE PELOTA] El jugador '" + this->session_manager->GetUserByColor(player->GetPlayerColor())->GetUsername()
									+ "' recupero la pelota para el equipo " + player->GetTeam()->GetName());
				} else {
					Logger::getInstance()->info("[RECUPERO DE PELOTA] LA IA del equipo " + player->GetTeam()->GetName() + " recupero la pelota");
				}
			}

			if (player->IsSelected()) {
                ball->SetLastOwner(player->GetTeam(), player->GetPlayerColor());
            } else {
                ball->SetLastOwner(player->GetTeam(), USER_COLOR::NO_COLOR);
            }
		}
	}
}

void GameServer::MovePlayersToDefaultPositions() {
	for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++) {
		Player* player_a = this->GetGameState()->GetMatch()->GetTeamA()->GetPlayerByPositionIndex(i);
		if (!player_a->IsSelected()) {
			player_a->GoBackToDefaultPosition();
		} else {
			player_a->Play();
		}
		Player* player_b = this->GetGameState()->GetMatch()->GetTeamB()->GetPlayerByPositionIndex(i);
		if (!player_b->IsSelected()) {
			player_b->GoBackToDefaultPosition();
		} else {
			player_b->Play();
		}
	}
}

void GameServer::MoveBall() {
	this->game_state->GetMatch()->GetBall()->Move();
}

bool GameServer::IsRunning() {
	return this->is_running;
}

void GameServer::DisconnectClient(ClientSocket* client) {
	if (this->session_manager->IsAuthenticatedClient(client)) {
		this->session_manager->CloseSession(client);
		if (this->session_manager->GetAutheticatedUsersCount() == 0) {
			this->is_running = false;
		}
	}
}

void GameServer::ChangeFormation(ChangeFormationRequest* cfRequest, int socket_id) {
	User* user = this->session_manager->GetUserBySocketID(socket_id);
	Team* team = user->GetSelectedPlayer()->GetTeam();
	team->GetFormation()->ChangeFormation(cfRequest->GetFormation());
	team->UpdateFormation();
	Logger::getInstance()->info(
			"(Server:HandleChangeFormationRequest) El usuario " + user->GetUsername() + " cambio la formacion de su equipo (" + team->GetName() + ") a "
					+ cfRequest->GetFormation());
	Logger::getInstance()->info(
			"(Server:HandleChangeFormationRequest) Nueva formacion (" + team->GetName() + "): " + to_string(team->GetFormation()->GetValue()));
}

int GameServer::GetTeamUsersNum(string team_name) {
	int num;
	map<string, User*> users = this->session_manager->GetAuthenticatedUsers();
	Team* user_team;
	Team* current_team;
	if (team_name == "a") {
		user_team = this->game_state->GetMatch()->GetTeamA();
	} else {
		user_team = this->game_state->GetMatch()->GetTeamB();
	}

	for (auto const& u : users) {
		current_team = u.second->GetSelectedPlayer()->GetTeam();
		if (current_team == user_team) {
			num++;
		}
	}

	return num;
}

void GameServer::UpdateMatchState() {
	this->game_state->UpdateMatchState();
}

void GameServer::Run() {
	this->UpdateMatchState();
	this->RunArtificialIntelligence();
}
