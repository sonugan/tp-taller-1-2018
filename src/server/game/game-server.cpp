#include "game-server.h"

#include "../../shared/logger.h"


GameServer::GameServer(Configuration* initial_configuration)
{
    this->game_state = new GameState(initial_configuration);
    this->session_manager = new SessionManager(initial_configuration->GetCredentials(), initial_configuration->GetMaxPlayers());
}

GameServer::~GameServer()
{
    delete this->game_state;
    delete this->session_manager;
}

GameState* GameServer::GetGameState()
{
    return this->game_state;
}

Player* GameServer::GetUserSelectedPlayer(std::vector<Player*> available_players)
{
    // TIENE QUE SER ALGUNO DE LOS DELANTEROS = POSICIONES 4, 5 O 6

    for (unsigned int i = 0; i < available_players.size(); i++)
    {
        Player* player = available_players[i];

        if (player->GetPositionIndex() >= 4 && player->GetPositionIndex() <= 6)
        {
            return player;
        }

    }

    return NULL;
}

void GameServer::DoLogin(ClientSocket* client, LoginRequest* login_request)
{
    User* authenticated_user = this->session_manager->Authenticate(client, login_request);

    // SETEO EL JUGADOR ACTIVO

    Team* selected_team = this->game_state->GetMatch()->GetTeamB();

    if (authenticated_user->GetSelectedTeam() == TEAM_NUMBER::TEAM_A)
    {
        selected_team = this->game_state->GetMatch()->GetTeamA();
    }

    Player* selected_player = this->GetUserSelectedPlayer(selected_team->GetAvailablePlayers());

    selected_player->SetPlayerColor(authenticated_user->GetUserColor());
    authenticated_user->SetSelectedPlayer(selected_player);

}

void GameServer::DoQuit(ClientSocket* client)
{
//    this->session_manager->CloseSession(client);
    this->DisconnectClient(client);
}

std::string GameServer::DoRecoverBall(RecoverBallRequest* recover_ball_request, int socket_id)
{
    User* user = this->session_manager->GetUserBySocketID(socket_id);
    user->GetSelectedPlayer()->RecoverBall();
    string game_state_serialize = this->game_state->GetMatch()->Serialize();
    return game_state_serialize;
}

std::string GameServer::DoKick(KickBallRequest* kick_request, int socket_id)
{
    User* user = this->session_manager->GetUserBySocketID(socket_id);
    user->GetSelectedPlayer()->Kick();
    return this->game_state->GetMatch()->Serialize();
}


Message* GameServer::DoPassBall(ClientSocket* client, PassBallRequest* pass_ball_request)
{
    Logger::getInstance()->debug("(GameServer::DoPassBall) REQUEST DE PASE RECIBIDO");
    User* user = this->session_manager->GetUserBySocketID(client->socket_id);
    user->GetSelectedPlayer()->PassBall();
    return new Message(this->game_state->GetMatch()->Serialize());
}

std::string GameServer::DoMove(MoveRequest* move_request, int socket_id)
{
    User* user = this->session_manager->GetUserBySocketID(socket_id);
    DIRECTION direction = move_request->GetDirection();
    bool running = move_request->IsRunning();
    if (direction == DIRECTION::NORTH)
    {
        user->GetSelectedPlayer()->MoveUp(running);
    }
    else if (direction == DIRECTION::SOUTH)
    {
        user->GetSelectedPlayer()->MoveDown(running);
    }
    else if (direction == DIRECTION::EAST)
    {
        user->GetSelectedPlayer()->MoveRight(running);
    }
    else if (direction == DIRECTION::WEST)
    {
        user->GetSelectedPlayer()->MoveLeft(running);
    }
    else if (direction == DIRECTION::NORTHEAST)
    {
        user->GetSelectedPlayer()->MoveUpToRight(running);
    }
    else if (direction == DIRECTION::NORTHWEST)
    {
        user->GetSelectedPlayer()->MoveUpToLeft(running);
    }
    else if (direction == DIRECTION::SOUTHEAST)
    {
        user->GetSelectedPlayer()->MoveDownToRight(running);
    }
    else if (direction == DIRECTION::SOUTHWEST)
    {
        user->GetSelectedPlayer()->MoveDownToLeft(running);
    }

    return this->game_state->GetMatch()->Serialize();

}

string GameServer::ChangePlayer(ChangePlayerRequest* change_player_request, int socket_id)
{
    User* user = this->session_manager->GetUserBySocketID(socket_id);
    Player* last_selected_player = user->GetSelectedPlayer();

    if (!last_selected_player->HasBall())
    {
        Player* next_player = NULL;
        Team* team = user->GetSelectedPlayer()->GetTeam();

        unsigned int new_selected_player_position_index = user->GetSelectedPlayer()->GetPositionIndex();

        for (unsigned int i = 0; i < (Team::TEAM_SIZE - 1); i++)
        {

            if (new_selected_player_position_index == Team::TEAM_SIZE-1)
            {
                new_selected_player_position_index = 0;
            }
            else
            {
                new_selected_player_position_index++;
            }

            Player* possible_player = team->GetPlayers()[new_selected_player_position_index];
            if (!possible_player->IsSelected())
            {
                next_player = possible_player;
                break;
            }
        }


        last_selected_player->SetPlayerColor(USER_COLOR::NO_COLOR);
        next_player->SetPlayerColor(user->GetUserColor());
        user->SetSelectedPlayer(next_player);
    }

    return this->game_state->GetMatch()->Serialize();
}

bool GameServer::IsReadyToStart()
{
    return this->session_manager->IsReadyToStart();
}

Message* GameServer::StartGame()
{
    Logger::getInstance()->info("(GameServer:StartGame) Comenzando el juego.");
    this->is_running = true;
    return new Message(this->game_state->GetMatch()->Serialize());
}

void GameServer::RunArtificialIntelligence() {
    this->CatchBall();
    this->MoveBall();
    this->MovePlayersToDefaultPositions();
}

void GameServer::CatchBall()
{
    if (this->GetGameState()->GetMatch()->GetBall()->LastFreedDelayPassed()) {
        for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
            Player* player_a = this->GetGameState()->GetMatch()->GetTeamA()->GetPlayers()[i];
            MakePlayerCatchBall(player_a);
            Player* player_b = this->GetGameState()->GetMatch()->GetTeamB()->GetPlayers()[i];
            MakePlayerCatchBall(player_b);
        }
    }

}

void GameServer::MakePlayerCatchBall(Player* player) {
    if (!player->HasBall())
    {
        Ball* ball = player->GetTeam()->GetMatch()->GetBall();
        int distance = ball->GetLocation()->Distance(player->GetLocation());
        if (ball->IsFree() && distance < CATCH_DISTANCE)
        {
            Trajectory* trajectory = new Trajectory(player);
            ball->SetTrajectory(trajectory);

            /*
            Si el jugador que agarra la pelota no estaba seleccionado,
            es seleccionado por el jugador del mismo equipo que estaba más cerca.
            */

            if (USER_COLOR::NO_COLOR == player->GetPlayerColor()) {

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

        }
    }
}

void GameServer::MovePlayersToDefaultPositions() {
    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        Player* player_a = this->GetGameState()->GetMatch()->GetTeamA()->GetPlayers()[i];
        if (!player_a->IsSelected()) {
            player_a->GoBackToDefaultPosition();
        }else{
            player_a->Play();
        }
        Player* player_b = this->GetGameState()->GetMatch()->GetTeamB()->GetPlayers()[i];
        if (!player_b->IsSelected()) {
            player_b->GoBackToDefaultPosition();
        }else{
            player_b->Play();
        }
    }
}

void GameServer::MoveBall() {
    this->game_state->GetMatch()->GetBall()->Move();
}

bool GameServer::IsRunning()
{
    return this->is_running;
}

void GameServer::DisconnectClient(ClientSocket* client)
{
    if(this->session_manager->IsAuthenticatedClient(client))
    {
        this->session_manager->CloseSession(client);
        if(this->session_manager->GetAutheticatedUsersCount() == 0)
        {
            this->is_running = false;
        }
    }
}
