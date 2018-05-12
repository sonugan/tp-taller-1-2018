#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "message.h"
#include "socket.h"
#include "socket-address.h"
#include "client-socket.h"

class ServerSocket : public Socket
{
    public:
        ServerSocket();
        ServerSocket(int socket_id);
        void Bind(SocketAddress address);
        void Listen(int max_queue_size);
        ClientSocket* Accept();
        void Send(Socket* client_socket, Message* request);
        Message* Receive(Socket* origin_socket, int expected_size);
        virtual ~ServerSocket();
    protected:
    private:
        SocketAddress address;
};

#endif // SERVERSOCKET_H
