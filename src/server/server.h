#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <thread>
#include <vector>
#include <deque>

#include "../shared/utils/queue.h"
#include "../shared/network/server-socket.h"
#include "../shared/network/client-socket.h"
#include "../shared/configuration/configuration.h"
#include "../shared/logger.h"
#include "login.cpp"

using namespace std;

class Server
{
    public:
        Server();
        Server(Configuration* config);
        virtual ~Server();

        void InitServer();

    protected:

    private:
        Queue<Message>* requests_queue;
        ServerSocket* socket;
        Queue<ClientSocket>* clients;
        u_int connected_user_count;
        u_int user_count;
        Configuration* config;
        void ConnectingUsers();
        void ListenConnections();
        bool ReadyToStart();
        void ManageLoginRequests(ClientSocket* client);
        u_int MAX_SOCKET_QUEUE_SIZE = 10;
};

#endif // SERVER_H
