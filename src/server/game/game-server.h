#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <map>
#include "../../shared/configuration/configuration.h"
#include "game/game-state.h"
#include "../../shared/network/login.cpp"
#include "session/session-manager.h"
#include "../../shared/network/messages/quit-request.h"

using namespace std;

class GameServer
{
public:
    GameServer(Configuration* initial_configuration);
    virtual ~GameServer();

    GameState* GetGameState();
    void DoLogin(Login* login_request);
    void DoQuit(QuitRequest* quit_request);


protected:

private:
    /* Attributes */
    GameState* game_state;
    bool is_running = false;
    SessionManager* session_manager;


};

#endif // GAMESERVER_H
