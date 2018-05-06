#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <thread>
#include <vector>
#include <deque>

#include "../shared/network/message-queue.h"
#include "../shared/network/queue.h"
#include "../shared/network/server-socket.h"
#include "../shared/network/client-socket.h"
#include "login.cpp"

using namespace std;

class Server
{
    public:
        Server();
        Server(u_int port, u_int user_count);
        virtual ~Server();

        void InitServer();

    protected:

    private:
        MessageQueue* requests_queue;
        ServerSocket* socket;
        deque<ClientSocket> clients;
        u_int clients_count;
        u_int user_count;
        void ConnectingUsers();
        void ListenConnections();
        bool ReadyToStart();
        void ManageClientConnection(ClientSocket client);
        void ManageClientConnections();
        u_int MAX_SOCKET_QUEUE_SIZE = 10;
};

#endif // SERVER_H
