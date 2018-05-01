#include<stdlib.h>

#include "socket.h"

using namespace std;

Socket::Socket()
{
    this->socket_id =  socket(AF_INET, SOCK_STREAM, 0);
    if (HasError(this->socket_id))
    {
       //throw(SocketException("ERROR: Opening socket"));
    }
}

Socket::Socket(int socket_id)
{
    this->socket_id = socket_id;
}

void Socket::Write(Socket client_socket, Message message)
{
    send(client_socket.socket_id, message.GetData(), message.GetDataSize(), 0);
}

Message Socket::Read(Socket client_socket, int expected_size)
{
    char* buffer = (char*) malloc(expected_size);

    if (HasError(read(client_socket.socket_id, buffer, expected_size)))
    {
        //throw(SocketException("ERROR reading from socket"));
    }
    Message m(buffer, expected_size);
    return m;
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
