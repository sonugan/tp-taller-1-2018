#include<stdlib.h>

#include "server-socket.h"

using namespace std;

ServerSocket::ServerSocket():Socket()
{

}

ServerSocket::ServerSocket(int socket_id):Socket(socket_id)
{
}

void ServerSocket::Bind(SocketAddress address)
{
    sockaddr_in addr = address.GetFormatted();
    if (HasError(bind(this->socket_id, (struct sockaddr *) &addr, sizeof(addr))))
    {
        Logger::getInstance()->debug("Error durante el binding");
    }
}

void ServerSocket::Listen(int max_queue_size)
{
    listen(this->socket_id,max_queue_size);
}

ServerSocket ServerSocket::Accept()
{
    sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);
    int client_socket_id = accept(this->socket_id, (struct sockaddr *) &client_address, &client_address_size);
    if (HasError(client_socket_id))
    {
        Logger::getInstance()->debug("Error mientras se esperaban conexiones");
        return NULL;
    }
    else
    {
        ServerSocket client(client_socket_id);
        SocketAddress addr(client_address);
        client.Bind(addr);
        return client;
    }
}

ServerSocket::~ServerSocket()
{
    //dtor
}
