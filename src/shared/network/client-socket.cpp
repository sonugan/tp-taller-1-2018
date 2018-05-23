#include "client-socket.h"
#include "../logger.h"
#include "exceptions/socket-connection-exception.h"

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

bool ClientSocket::Send(Message request)
{
    string data(request.GetData());
    string data_size = to_string(request.GetDataSize());
    Logger::getInstance()->debug("(ClientSocket:Send) data: " + data + " size: " + data_size);
    int sent_bytes = send(socket_id, request.GetData(), request.GetDataSize(), 0);

    bool sent_ok = sent_bytes > 0;
    if (sent_bytes <= 0)
    {
        Logger::getInstance()->debug("(ClientSocket:Send) Error al enviar mensaje.");
    }
    return sent_ok;
}

Message* ClientSocket::Receive(int expected_size)
{
    char buffer[expected_size];
    bzero(buffer,expected_size);

    Logger::getInstance()->debug("(ClientSocket:Receive) Ejecutando recv sobre el socket");

    int received_bytes = recv(this->socket_id, buffer, expected_size, 0);

    if (received_bytes <= 0)
    {
        Logger::getInstance()->debug("ERROR leyendo desde socket");
        throw SocketConnectionException("Error de conexión mientras se ejecutaba recv");
    }
    const string message_data = string(buffer);
    Logger::getInstance()->debug("(ClientSocket:Receive) Mensaje recibido: " + message_data);
    return new Message(message_data);
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
