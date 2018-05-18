#ifndef CLIENT_H
#define CLIENT_H

#include "../shared/configuration/configuration.h"
#include "../shared/network/client-socket.h"
#include "../shared/network/messages/login-request.h"
#include "../shared/network/messages/quit-request.h"

#include <string>

class Client
{
    public:
        Client(Configuration * configuration);
        virtual ~Client();
        void Init(std::string server_ip);
        bool LogIn(LoginRequest* login_request);
        bool Quit(QuitRequest* quit_request);
        void Close();

        // TODO: Tipar mensaje. esto es solo para una prueba
        void SendEvent();

    protected:

    private:
        Configuration* config;
        ClientSocket* clientSocket;
};

#endif // CLIENT_H
