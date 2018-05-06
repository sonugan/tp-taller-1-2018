#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <netinet/in.h>
#include "socket-address.h"

#include "socket.h"

class ClientSocket : public Socket
{
    public:
        ClientSocket();
        ClientSocket(int socket_id);
        void Connect(SocketAddress address);
        virtual ~ClientSocket();
        void Send(Request request);
        Message Receive(int expected_size);
        void Bind(SocketAddress address);
    protected:
    private:
        SocketAddress address;
};

#endif // CLIENTSOCKET_H
