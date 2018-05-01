#include "client-socket.h"

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

ClientSocket::~ClientSocket()
{
    //dtor
}
