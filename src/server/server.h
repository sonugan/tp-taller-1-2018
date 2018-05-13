#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <thread>
#include <vector>
#include <deque>
#include <utility>
#include <mutex>

#include "../shared/utils/queue.h"
#include "../shared/network/server-socket.h"
#include "../shared/network/client-socket.h"
#include "../shared/configuration/configuration.h"
#include "../shared/logger.h"
#include "login.cpp"
#include "session/session-manager.h"
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
    Queue<ClientSocket>* clients;
    u_int connected_user_count = 0;
    u_int user_count;
    u_int MAX_SOCKET_QUEUE_SIZE = 10;
    mutex server_mutex;
    SessionManager* session_manager;
    GameServer* game;


    /* Methods */
    void ConnectingUsers();
    void ListenConnections();
    bool ReadyToStart();
    void ReceiveMessages(ClientSocket* client);
    void ProcessMessage(ClientSocket* client, Message* message);
};

#endif // SERVER_H
