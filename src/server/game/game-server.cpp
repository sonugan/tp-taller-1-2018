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
