#include "client.h"

#include "../shared/network/client-socket.h"
#include "../shared/network/socket-address.h"
#include "../shared/utils/string-utils.h"
#include "../shared/network/login.cpp"
#include "../shared/logger.h"

Client::Client(Configuration* config)
{
    this->config = config;
}

Client::~Client()
{
    //dtor
}

void Client::Init()
{
    ClientSocket clientSocket;
    SocketAddress address(this->config->GetPort(), this->config->GetServerHostname().c_str());
    //SocketAddress address(51717, "localhost");
    clientSocket.Connect(address);

    bool is_logued = false;
    do
    {
        printf("Escribí tu usuario: ");
        char buffer[256];
        bzero(buffer,256);
        fgets(buffer,255,stdin);

        string username = string(buffer);
        username = StringUtils::RemoveLastNewLine(username);

        printf("Escribí tu password: ");
        bzero(buffer,256);
        fgets(buffer,255,stdin);

        string password = string(buffer);
        password = StringUtils::RemoveLastNewLine(password);
        //Request r(s);
        Login l(username, password);
        //Request r(&l);
        Message r(l.Serialize());
        clientSocket.Send(r);

        Message login_status = clientSocket.Receive(255);
        Logger::getInstance()->debug("(Client) login data: " + string(login_status.GetData()));
        Logger::getInstance()->debug("(Client) login size: " + to_string(login_status.GetDataSize()));
        if(string(login_status.GetData()) == "ok")
        {
            is_logued = true;
            cout << "Login success" << endl;
        }
    }
    while (!is_logued);

    clientSocket.ShutDownSends();
    clientSocket.ShutDown();

}
