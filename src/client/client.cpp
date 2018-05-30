#include "client.h"

#include "../shared/network/client-socket.h"
#include "../shared/network/socket-address.h"
#include "../shared/utils/string-utils.h"
#include "../shared/network/messages/login-request.h"
#include "../shared/logger.h"
#include "../shared/network/exceptions/socket-connection-exception.h"
#include <thread>

Client::Client(Configuration* config)
{
    this->config = config;
    clientSocket = new ClientSocket();
    this->message_queue = new SafeQueue<Message>();
    this->health_checked = std::chrono::system_clock::now();
}

Client::~Client() {
    delete clientSocket;
}

void Client::Init(string server_ip)
{
    SocketAddress address(this->config->GetPort(), this->config->GetServerHostname());
    clientSocket->Connect(address);

}

std::string Client::LogIn(LoginRequest* login_request) {
    try {
        Message r(login_request->Serialize());

        Logger::getInstance()->debug("(Client:LogIn) Enviando login request");
        clientSocket->Send(r);

        Logger::getInstance()->debug("(Client:LogIn) Esperando login response");

        // OJO con esto. Recibe bloquea el thread.
        Message* login_status = clientSocket->Receive(300);
        string login_response(login_status->GetData());
        Logger::getInstance()->debug("(Client) login data: " + login_response);
        Logger::getInstance()->debug("(Client) login size: " + to_string(login_status->GetDataSize()));
        return login_response;
    } catch (...) {
        Logger::getInstance()->error("(Client:LogIn) Error al intentar loguearse.");
        return "login-fail";
    }

}

std::string Client::WaitForGameStart() {
    try {

        // OJO con esto. Recibe bloquea el thread.
        // Espero el primer estado del juego para instanciar el modelo.
        Message* server_message = clientSocket->Receive(300);
        this->is_connected = true;

        //Empiezo a escuchar actualizaciones del modelo.
        receive_messages_thread = new thread(&Client::ReceiveMessages, this);

        thread health_check_sender(&Client::SendHealthCheck, this);
        health_check_sender.detach();

        return std::string(server_message->GetData());
    } catch (...) {
        return false;
    }

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
    return clientSocket->Send(r);;
}

bool Client::RecoverBall(RecoverBallRequest* recover_ball_request){
    Message r(recover_ball_request->Serialize());
    return clientSocket->Send(r);
}

bool Client::ChangePlayer(ChangePlayerRequest* change_player_request){
    Message r(change_player_request->Serialize());
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

void Client::ReceiveMessages()
{
    Logger::getInstance()->debug("(Client:ReceiveMessages) Iniciando hilo receptor de mensajes.");

    while(this->is_connected)
    {
        Logger::getInstance()->debug("(Client:ReceiveMessages) Esperando mensajes entrantes...");

        try
        {
            Message* incoming_message = this->clientSocket->Receive(300);
//            Logger::getInstance()->debug("(Client:ReceiveMessages) Recibido: " + string(incoming_message->GetData()));
            this->message_queue->Append(incoming_message);
        }
        catch (SocketConnectionException e)
        {
            Logger::getInstance()->error("(Client:ReceiveMessages) Error de conexión. Cerrando socket.");
            this->is_connected = false;
            clientSocket->Close();
        }
    }
}

void Client::SetMatch(Match* match)
{
    this->match = match;
}

string Client::GetGameState()
{
    if(this->message_queue->HasNext())
    {
        string data = string(this->message_queue->Next()->GetData());
        vector<string> splited_data = StringUtils::Split(data, '|');
        string new_id = splited_data[splited_data.size() - 1];

        while(current_match_state.compare(new_id) == 0)
        {
            if(this->message_queue->HasNext())
            {
                data = string(this->message_queue->Next()->GetData());
                if(!data.empty())
                {
                    splited_data = StringUtils::Split(data, '|');
                    if(splited_data.size() > 0)
                    {
                        new_id = splited_data[splited_data.size() - 1];
                    }
                }
            }
            else
            {
                current_match_state = new_id;
                return "";
            }
        }
        current_match_state = new_id;
        this->health_checked = std::chrono::system_clock::now();
        return data;
    }
    else
    {
        unsigned int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>
                             (std::chrono::system_clock::now() - this->health_checked).count();
        if(elapsed_millis > 15000)
        {
            is_connected = false;
        }
    }
    return "";
}

bool Client::IsConnected()
{
    return this->is_connected;
}

void Client::SendHealthCheck()
{
    while (this->is_connected) {
        HealthCheck* health_check = new HealthCheck();
        Logger::getInstance()->debug("(Client:SendHealthCheck) Enviando ping.");
        Message ping(health_check->Serialize());
        this->clientSocket->Send(ping);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        delete health_check;
    }
}
