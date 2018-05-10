#ifndef SOCKETCONNECTIONEXCEPTION_H
#define SOCKETCONNECTIONEXCEPTION_H

#include <string>
#include <stdexcept>

class SocketConnectionException : public std::runtime_error
{
    public:
        explicit SocketConnectionException(const std::string& error_message) :
            std::runtime_error(error_message) {};
        virtual ~SocketConnectionException(){};

    protected:

    private:
};

#endif // SOCKETCONNECTIONEXCEPTION_H
