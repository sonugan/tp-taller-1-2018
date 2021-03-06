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
#include "../../shared/network/messages/long-pass-request.h"
#include "../../shared/network/messages/move-request.h"
#include "../../shared/network/messages/change-player-request.h"
#include "../../shared/network/messages/change-formation-request.h"

using namespace std;

class GameServer
{
public:
    GameServer(Configuration* initial_configuration);
    virtual ~GameServer();

    GameState* GetGameState();
    void DoLogin(ClientSocket* client, LoginRequest* login_request);
    void DoQuit(ClientSocket* client);
    Location* FindNearestPlayer(Player* player);
    void DoRecoverBall(RecoverBallRequest* recover_ball_request, int socket_id);
    void DoMove(MoveRequest* move_request, int socket_id);
    void DoKick(KickBallRequest* kick_ball_request, int client_socket_id);
    void DoLongPass(LongPassRequest* long_pass_request, int client_socket_id);
    void DoPassBall(ClientSocket* client, PassBallRequest* pass_ball_request);
    void ChangePlayer(ChangePlayerRequest* change_player_request, int socket_id);
    bool IsReadyToStart();
    void StartGame();
    bool IsRunning();
    void DisconnectClient(ClientSocket* client);
    void ChangeFormation(ChangeFormationRequest* change_player_request, int socket_id);
    bool TeamsHaveFormation();
    int GetTeamUsersNum(string team_name);
    void Run();
    void DetectBallTouches();
    void MoveKeepers();
protected:
    void ReturnBallToKeeperOnGoalKick(Ball* ball);
    void DetectGoals(Ball* ball);
    void BounceBallOnThrowIn(Ball* ball);
    void BounceBallOnGoalPost(Ball* ball);
private:
	static const int CATCH_DISTANCE = 30;
    /* Attributes */
    GameState* game_state;
    bool is_running = false;
    SessionManager* session_manager;

    Player* GetUserSelectedPlayer(std::vector<Player*> available_players);
    void CatchBall();
    void MakePlayerCatchBall(Player* player, Ball* ball);
    void MoveBall();
    void MovePlayersToDefaultPositions();
    void UpdateMatchState();
    void RunArtificialIntelligence();

};

#endif // GAMESERVER_H
