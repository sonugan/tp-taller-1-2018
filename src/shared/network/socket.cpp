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

//void Socket::Send(Socket client_socket, Request request)
//{
//    send(client_socket.socket_id, request.GetData(), request.GetDataSize(), 0);
//}
//
//Message Socket::Receive(Socket client_socket, int expected_size)
//{
//    char* buffer = (char*) malloc(expected_size);
//
//    if (HasError(read(client_socket.socket_id, buffer, expected_size)))
//    {
//        Logger::getInstance()->debug("ERROR leyendo desde socket");
//    }
//    Message m(buffer, expected_size);
//    return m;
//}

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
