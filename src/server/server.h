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

#include "../shared/utils/queue.h"
#include "../shared/network/server-socket.h"
#include "../shared/network/client-socket.h"
#include "../shared/configuration/configuration.h"
#include "../shared/logger.h"
#include "messages/login-request.h"
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
    std::mutex output_msg_mutex;
    std::condition_variable output_msg_condition_variable;
    GameServer* game;
    map<int, Queue<Message> *> outgoing_msg_queues = {};


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
    void SendMessage(ClientSocket* client);
};

#endif // SERVER_H
