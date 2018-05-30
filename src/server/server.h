#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <thread>
#include <vector>
#include <deque>
#include <utility>
#include <mutex>
#include <map>
#include <condition_variable>
#include <chrono>

#include "../shared/utils/queue.h"
#include "../shared/utils/safe-queue.h"
#include "../shared/utils/id-generator.h"
#include "../shared/network/server-socket.h"
#include "../shared/network/client-socket.h"
#include "../shared/configuration/configuration.h"
#include "../shared/logger.h"
#include "../shared/network/messages/login-request.h"
#include "game/game-server.h"

using namespace std;

class Server
{
public:
    Server();
    Server(Configuration* config);
    virtual ~Server();

    void Init();

protected:

private:
    int port;
    Queue<pair<ClientSocket*, Message*>>* message_queue;
    ServerSocket* socket;
    map<int, ClientSocket*> clients = {};
    u_int user_count;
    u_int MAX_SOCKET_QUEUE_SIZE = 10;
    std::mutex server_mutex;
    std::mutex input_msg_mutex;
    std::condition_variable input_msg_condition_variable;

    GameServer* game;
    map<int, SafeQueue<Message> *> outgoing_msg_queues = {};
    map<int, std::chrono::time_point<std::chrono::system_clock>> timers = {};

    /* Methods */
    void ConnectingUsers();
    void ListenConnections();
    void ReceiveMessages(ClientSocket* client);
    void ProcessMessage(ClientSocket* client, Message* message);
    void NotifyAll(Message* message);
    void HandleLoginRequest(ClientSocket* client, Message* message);
    void HandleQuitRequest(ClientSocket* client, Message* message);
    void HandleMoveRequest(ClientSocket* client, Message* message);
    void HandleRecoverBallRequest(ClientSocket* client, Message* message);
    void HandleKickRequest(ClientSocket* client, Message* message);
    void HandlePassBallRequest(ClientSocket* client, Message* message);
    void HandleChangePlayerRequest(ClientSocket* client, Message* message);
    void HandleHealthCheck(ClientSocket* client, Message* message);
    void SendMessage(ClientSocket* client);
    void NotifyGameState();
    void DisconnectClient(ClientSocket* client);
    void CheckDisconnections();
    void RestartTimers();
    u_int SEND_GAME_STATE_EVERY_MILLISECONDS = 40;
    u_int CONNECTION_TIMEOUT = 3000;
};

#endif // SERVER_H
