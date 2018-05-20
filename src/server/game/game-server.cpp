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
    for (unsigned int i = 0; i < available_players.size(); i++) {
        Player* player = available_players[i];

        if (player->GetPositionIndex() >= 4 && player->GetPositionIndex() <= 6) {
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

void GameServer::DoQuit(QuitRequest* quit_request)
{
    this->session_manager->RemoveSession(quit_request->GetUsername());
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


Message GameServer::DoPassBall(ClientSocket* client, PassBallRequest* pass_ball_request)
{
    User* user = this->session_manager->GetUserBySocketID(client->socket_id);
    user->GetSelectedPlayer()->PassBall();
    Message response(this->game_state->GetMatch()->Serialize());
    return response;
}

std::string GameServer::DoMove(MoveRequest* move_request, int socket_id){
    User* user = this->session_manager->GetUserBySocketID(socket_id);
    DIRECTION direction = move_request->GetDirection();
    bool running = move_request->IsRunning();
    if (direction == DIRECTION::NORTH){
        user->GetSelectedPlayer()->MoveUp(running);
    }else if (direction == DIRECTION::SOUTH){
        user->GetSelectedPlayer()->MoveDown(running);
    }else if (direction == DIRECTION::EAST){
        user->GetSelectedPlayer()->MoveRight(running);
    }else if (direction == DIRECTION::WEST){
        user->GetSelectedPlayer()->MoveLeft(running);
    }else if (direction == DIRECTION::NORTHEAST){
        user->GetSelectedPlayer()->MoveUpToRight(running);
    }else if (direction == DIRECTION::NORTHWEST){
        user->GetSelectedPlayer()->MoveUpToLeft(running);
    }else if (direction == DIRECTION::SOUTHEAST){
        user->GetSelectedPlayer()->MoveDownToRight(running);
    }else if (direction == DIRECTION::SOUTHWEST){
        user->GetSelectedPlayer()->MoveDownToLeft(running);
    }
    return this->game_state->GetMatch()->Serialize();

}

string GameServer::ChangePlayer(ChangePlayerRequest* change_player_request, int socket_id)
{
    User* user = this->session_manager->GetUserBySocketID(socket_id);
    Player* last_selected_player = user->GetSelectedPlayer();
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

    return this->game_state->GetMatch()->Serialize();
}
