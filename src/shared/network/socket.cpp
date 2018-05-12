#include<stdlib.h>

#include "socket.h"

using namespace std;

Socket::Socket()
{
    this->socket_id =  socket(AF_INET,
        SOCK_STREAM, //TCP
        //SOCK_DGRAM,//UDP
        0);
    if (HasError(this->socket_id))
    {
       Logger::getInstance()->debug("ERROR: Abriendo socket");
    }
}

Socket::Socket(int socket_id)
{
    this->socket_id = socket_id;
}

void Socket::ShutDownReceives()
{
    shutdown(this->socket_id, SHUT_RD);
}

void Socket::ShutDownSends()
{
    shutdown(this->socket_id, SHUT_WR);
}

void Socket::ShutDown()
{
    shutdown(this->socket_id, SHUT_RDWR);
}

void Socket::Close()
{
    //ShutDown();
    close(this->socket_id);
}

Socket::~Socket()
{
    //dtor
}

bool Socket::HasError(int result)
{
    return result<0;
}
