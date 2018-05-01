#ifndef SOCKET_H
#define SOCKET_H

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "message.h"
#include "../logger.h"
#include "../utils/string-builder.h"

class Socket
{
    public:
        Socket();
        Socket(int socket_id);
        virtual ~Socket();
        void Send(Socket client_socket, Message message);
        Message Read(Socket client_socket, int expected_size);
        void ShutDown();
        void Close();
    protected:
        int socket_id;
        bool HasError(int result);
    private:

};

#endif // SOCKET_H
