#include "client.h"

#include "../shared/network/client-socket.h"
#include "../shared/network/socket-address.h"
#include "../shared/utils/string-utils.h"
#include "../shared/network/messages/login-request.h"
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

bool Client::LogIn(LoginRequest* login_request) {
        Message r(login_request->Serialize());
        clientSocket->Send(r);

        // OJO con esto. Recibe bloquea el thread.
        Message login_status = clientSocket->Receive(255);
        Logger::getInstance()->debug("(Client) login data: " + string(login_status.GetData()));
        Logger::getInstance()->debug("(Client) login size: " + to_string(login_status.GetDataSize()));
        return string(login_status.GetData()) == "login-ok";
}

bool Client::KickBall(KickBallRequest* kick_ball_request){
    Message r(kick_ball_request->Serialize());
    return clientSocket->Send(r);
}

bool Client::Move(MoveRequest* move_request){
    Message r(move_request->Serialize());
    return clientSocket->Send(r);
}

bool Client::PassBall(PassBallRequest* pass_ball_request){
    Message r(pass_ball_request->Serialize());
    return clientSocket->Send(r);
}

bool Client::RecoverBall(RecoverBallRequest* recover_ball_request){
    Message r(recover_ball_request->Serialize());
    return clientSocket->Send(r);
}



bool Client::Quit(QuitRequest* quit_request)
{
    Logger::getInstance()->debug("(Client:Quit) Enviando quit request.");
    Message message_quit_request(quit_request->Serialize());
    delete quit_request;
    return this->clientSocket->Send(message_quit_request);
}

void Client::Close() {
    clientSocket->ShutDownSends();
    clientSocket->ShutDown();
}

void Client::SendEvent()
{
    Logger::getInstance()->debug("(Client:Quit) Enviando move request.");
    Message event("6|move-request");
    this->clientSocket->Send(event);
}
