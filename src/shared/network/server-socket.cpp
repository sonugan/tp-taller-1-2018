#include<stdlib.h>

#include "server-socket.h"
#include "exceptions/socket-connection-exception.h"

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
        Logger::getInstance()->debug("(ServerSocket:Bind) Error durante el binding.");
    }
    this->address = address;
}

void ServerSocket::Listen(int max_queue_size)
{
    listen(this->socket_id,max_queue_size);
}

ClientSocket* ServerSocket::Accept()
{
    sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);
    int client_socket_id = accept(this->socket_id, (struct sockaddr *) &client_address, &client_address_size);
    if (HasError(client_socket_id))
    {
        Logger::getInstance()->debug("(ServerSocket:Accept) Error mientras se esperaban conexiones.");
        return NULL;
    }
    else
    {
        Logger::getInstance()->debug("(ServerSocket:Accept) Conexión aceptada. Se crea nuevo socket.");
        ClientSocket* client = new ClientSocket(client_socket_id);
        return client;
    }
}

void ServerSocket::Send(Socket* client_socket, Message* request)
{
    string data = string(request->GetData());
    string data_size = to_string(request->GetDataSize());
    Logger::getInstance()->debug("(ServerSocket:Send) data: " + data + " size: " + data_size);
    send(client_socket->socket_id, request->GetData(), request->GetDataSize(), 0);
    delete request;
}

Message* ServerSocket::Receive(Socket* client_socket, int expected_size)
{
    //char* buffer = (char*) malloc(expected_size);
    char buffer[expected_size];
    bzero(buffer,expected_size);

    int received_bytes = read(client_socket->socket_id, buffer, expected_size);

    if (received_bytes <= 0)
    {
        Logger::getInstance()->error("(ServerSocket:Receive) Bytes recibidos: " + to_string(received_bytes));
        throw SocketConnectionException("Error de conexión mientras se ejecutaba read");
    }

    Logger::getInstance()->debug("(ServerSocket::Receive) received_bytes:" + to_string(received_bytes));

    string message_data = string(buffer);
    return new Message(message_data);
}

ServerSocket::~ServerSocket()
{
    //dtor
}
