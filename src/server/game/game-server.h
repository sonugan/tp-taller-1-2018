#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <map>
#include "../../shared/configuration/configuration.h"
#include "game-state.h"
#include "../../shared/network/messages/login-request.h"
#include "../session/session-manager.h"
#include "../../shared/network/messages/quit-request.h"
#include "../../shared/network/messages/recover-ball-request.h"
#include "../../shared/network/messages/kick-ball-request.h"
#include "../../shared/network/client-socket.h"
#include "../../shared/network/messages/pass-ball-request.h"
#include "../../shared/network/messages/move-request.h"
#include "../../shared/network/messages/change-player-request.h"

using namespace std;

class GameServer
{
public:
    GameServer(Configuration* initial_configuration);
    virtual ~GameServer();

    GameState* GetGameState();
    void DoLogin(ClientSocket* client, LoginRequest* login_request);
    void DoQuit(ClientSocket* client);
    std::string DoRecoverBall(RecoverBallRequest* recover_ball_request, int socket_id);
    std::string DoMove(MoveRequest* move_request, int socket_id);
    string DoKick(KickBallRequest* kick_ball_request, int client_socket_id);
    Message* DoPassBall(ClientSocket* client, PassBallRequest* pass_ball_request);
    string ChangePlayer(ChangePlayerRequest* change_player_request, int socket_id);
    bool IsReadyToStart();
    Message* StartGame();
    void PlayerCatchBall(int socket_id);
    bool IsRunning();
    void DisconnectClient(ClientSocket* client);

protected:

private:
    /* Attributes */
    GameState* game_state;
    bool is_running = false;
    SessionManager* session_manager;

    Player* GetUserSelectedPlayer(std::vector<Player*> available_players);

};

#endif // GAMESERVER_H
