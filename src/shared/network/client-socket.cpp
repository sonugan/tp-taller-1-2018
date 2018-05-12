#include "client-socket.h"
#include "../logger.h"

ClientSocket::ClientSocket() : Socket()
{

}

ClientSocket::ClientSocket(int socket_id) : Socket(socket_id)
{
    //ctor
}

void ClientSocket::Connect(SocketAddress server_address)
{
    sockaddr_in addr = server_address.GetFormatted();
    if(HasError(connect(this->socket_id, (struct sockaddr *) &addr, sizeof(addr))))
    {
        Logger::getInstance()->debug("ERROR conectandose al servidor");
    }
}

void ClientSocket::Send(Message request)
{
    string data(request.GetData());
    string data_size = to_string(request.GetDataSize());
    Logger::getInstance()->debug("(ClientSocket:Send) data: " + data + " size: " + data_size);
    send(socket_id, request.GetData(), request.GetDataSize(), 0);
}

Message ClientSocket::Receive(int expected_size)
{
    char* buffer = (char*) malloc(expected_size);
    bzero(buffer,expected_size);

    if (HasError(read(this->socket_id, buffer, expected_size)))
    {
        Logger::getInstance()->debug("ERROR leyendo desde socket");
    }
    string message_data = string(buffer);
    Message m(message_data);
    return m;
}

ClientSocket::~ClientSocket()
{
    //dtor
}

void ClientSocket::Bind(SocketAddress address)
{
    sockaddr_in addr = address.GetFormatted();
    if (HasError(bind(this->socket_id, (struct sockaddr *) &addr, sizeof(addr))))
    {
        Logger::getInstance()->debug("Error durante el binding");
    }
    this->address = address;
}
