#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <map>
#include "../../shared/configuration/configuration.h"
#include "game/game-state.h"
#include "../../shared/network/messages/login-request.h"
#include "session/session-manager.h"
#include "../../shared/network/messages/quit-request.h"
#include "../../shared/network/messages/recover-ball-request.h"
#include "../../shared/network/client-socket.h"

using namespace std;

class GameServer
{
public:
    GameServer(Configuration* initial_configuration);
    virtual ~GameServer();

    GameState* GetGameState();
    void DoLogin(ClientSocket* client, LoginRequest* login_request);
    void DoQuit(QuitRequest* quit_request);
    std::string DoRecoverBall(RecoverBallRequest* recover_ball_request, int socket_id);


protected:

private:
    /* Attributes */
    GameState* game_state;
    bool is_running = false;
    SessionManager* session_manager;

    Player* GetUserSelectedPlayer(std::vector<Player*> available_players);

};

#endif // GAMESERVER_H
