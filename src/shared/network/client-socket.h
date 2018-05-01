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
    protected:
    private:
};

#endif // CLIENTSOCKET_H
