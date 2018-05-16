#include "client.h"

#include "../shared/network/client-socket.h"
#include "../shared/network/socket-address.h"
#include "../shared/utils/string-utils.h"
#include "../shared/network/login.cpp"
#include "../shared/logger.h"

Client::Client(Configuration* config)
{
    this->config = config;
    clientSocket = new ClientSocket();
}

Client::~Client() {
    delete clientSocket;
}

void Client::Init(string server_ip)
{
    SocketAddress address(this->config->GetPort(), server_ip);
    clientSocket->Connect(address);

}

bool Client::LogIn(Login* login) {
        Message r(login->Serialize());
        clientSocket->Send(r);

        // OJO con esto. Recibe bloquea el thread.
        Message login_status = clientSocket->Receive(255);
        Logger::getInstance()->debug("(Client) login data: " + string(login_status.GetData()));
        Logger::getInstance()->debug("(Client) login size: " + to_string(login_status.GetDataSize()));
        return string(login_status.GetData()) == "login-ok";
}

bool Client::Quit(QuitRequest* quit_request)
{
    Logger::getInstance()->debug("(Client:Quit) Enviando quit request.");
    Message message_quit_request(quit_request->Serialize());
    delete quit_request;
    return this->clientSocket->Send(quit_request);
}

void Client::Close() {
    clientSocket->ShutDownSends();
    clientSocket->ShutDown();
}
