#ifndef CLIENT_H
#define CLIENT_H

#include "../shared/configuration/configuration.h"
#include "../shared/network/client-socket.h"
#include "../shared/network/login.cpp"
#include "../shared/network/messages/quit-request.h"

#include <string>

class Client
{
    public:
        Client(Configuration * configuration);
        virtual ~Client();
        void Init(std::string server_ip);
        bool LogIn(Login* login);
        bool Quit();
        void Close();

    protected:

    private:
        Configuration* config;
        ClientSocket* clientSocket;
};

#endif // CLIENT_H
