#include "socket-connection-exception.h"

SocketConnectionException::SocketConnectionException(const std::string& error_message):
    std::runtime_error(error_message)
{
    //ctor
}

SocketConnectionException::~SocketConnectionException()
{
    //dtor
}
