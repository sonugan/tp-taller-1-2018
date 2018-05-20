#include "server.h"

#include "../shared/network/exceptions/socket-connection-exception.h"
#include "session/authentication-exception.h"
#include "session/max-allowed-user-exception.h"
#include "../shared/network/messages/quit-request.h"
#include "../shared/network/messages/pass-ball-request.h"

Server::Server(Configuration* config)
{
    Logger::getInstance()->info("Iniciando servidor en puerto:'"
                                + to_string(config->GetPort()) + "' y capacidad para '"
                                + to_string(config->GetMaxPlayers()) + "' usuarios.");

    this->message_queue = new Queue<pair<ClientSocket*, Message*>>();
    this->port = config->GetPort();
    this->user_count = config->GetMaxPlayers();
    this->socket = new ServerSocket();
    this->game = new GameServer(config);
}

Server::~Server()
{
    delete this->message_queue;
    delete this->socket;
    delete this->game;
}

void Server::Init()
{
    this->socket->Bind(this->port);
    this->socket->Listen(MAX_SOCKET_QUEUE_SIZE);

    this->ConnectingUsers();

    Logger::getInstance()->info("Comenzando el juego....'");

    this->socket->Close();

    Logger::getInstance()->info("Cerrando el servidor....'");
}

/* Private Methods */

void Server::ConnectingUsers()
{
    thread wait_connections_thread(&Server::ListenConnections, this);

    // TODO: ver cómo cortar este loop, si es que tiene sentido hacerlo
    while(true)
    {
        // TODO: pensar bien donde meter esto!
        unique_lock<mutex> lock(input_msg_mutex);
        while(!this->message_queue->HasNext())
        {
            input_msg_condition_variable.wait(lock);
        }
        Logger::getInstance()->debug("(Server:ConnectingUsers) Desencolando mensaje para procesar");
        auto msg = this->message_queue->Next();
        ClientSocket* client = msg->first;
        Message* message = msg->second;
        this->ProcessMessage(client, message);

    }
    pthread_cancel(wait_connections_thread.native_handle());
    wait_connections_thread.join();
}

void Server::ListenConnections()
{
    Logger::getInstance()->debug("(Server:ListenConnections) Escuchando conexiones....'");
    // TODO: averiguar como manejar este vector de theards. tiene sentido??
    vector<thread> client_threads;

    // TODO: ver cómo cortar este loop, si es que tiene sentido hacerlo
    while(true)
    {
        Logger::getInstance()->debug("(Server:ListenConnections) Previo Accept().");
        // Accept() bloquea el hilo hasta que un cliente intenta conectarse.
        ClientSocket* client = this->socket->Accept();

        unique_lock<mutex> lock(server_mutex);

        Logger::getInstance()->debug("(Server:ListenConnections) Agregando nuevo ClientSocket a colección de clientes.");
        this->clients[client->socket_id] = client;
        client_threads.push_back(thread(&Server::ReceiveMessages, this, client));

        Queue<Message>* outgoing_msg_queue = new Queue<Message>();
        this->outgoing_msg_queues[client->socket_id] = outgoing_msg_queue;
        // Disparo thread para envi ar mensajes a este ClienteSocket.
        thread outgoing_msg_thread(&Server::SendMessage, this, client);
        outgoing_msg_thread.detach();
    }
}

void Server::ReceiveMessages(ClientSocket* client)
{
    string socket_id = to_string(client->socket_id);
    Logger::getInstance()->debug("(Server:ReceiveMessages) Iniciando hilo receptor de mensajes. ClientSocket: " + socket_id);
    bool receiving_messages = true;
    while(receiving_messages)
    {
        Logger::getInstance()->debug("(Server:ReceiveMessages) Esperando mensajes entrantes...");

        Message* incoming_message;
        try
        {
            incoming_message = this->socket->Receive(client, 255);
            Logger::getInstance()->debug("(Server:ReceiveMessages) Mensaje recibido. Encolando para ser procesado.");
            // Aplico lock (mutex)  antes de enconlar el mensaje entrante.
            unique_lock<mutex> lock(input_msg_mutex);

            auto p_msg = make_pair(client, incoming_message);
            this->message_queue->Append(&p_msg);

            input_msg_condition_variable.notify_all();
        }
        catch (SocketConnectionException e)
        {
            Logger::getInstance()->error("(Server) Error de conexión. Cerrando socket cliente.");
            receiving_messages = false;
            client->Close();
        }
    }
}

void Server::ProcessMessage(ClientSocket* client, Message* message)
{
    Logger::getInstance()->debug("(Server::ProcessMessage) Procesando mensaje.");

    switch(message->GetType())
    {
    case MESSAGE_TYPE::LOGIN_REQUEST:
        this->HandleLoginRequest(client, message);
        break;
    case MESSAGE_TYPE::QUIT_REQUEST:
        this->HandleQuitRequest(client, message);
        break;
    case MESSAGE_TYPE::MOVE_REQUEST:
        this->HandleMoveRequest(client, message);
        break;
    case MESSAGE_TYPE::RECOVER_REQUEST:
        this->HandleRecoverBallRequest(client, message);
        break;
    case MESSAGE_TYPE::KICK_REQUEST:
        this->HandleKickRequest(client, message);
        break;
    case MESSAGE_TYPE::SELECT_REQUEST:
        this->HandleChangePlayerRequest(client, message);
        break;
    default:
        Logger::getInstance()->debug("(Server::ProcessMessage) No hay handler para este tipo de mensaje.");
    }
}

void Server::HandleLoginRequest(ClientSocket* client, Message* message)
{
    Logger::getInstance()->debug("(Server:HandleLoginRequest) Procesando login request.");
    LoginRequest login_request;
    message->GetDeserializedData(&login_request);

    try
    {
        this->game->DoLogin(client, &login_request);
        Message* login_response = new Message("9|960|540|3|0|0|0|360|540|3|0|0|0|660|240|3|0|0|0|660|540|3|0|0|0|660|840|3|0|0|0|800|240|3|0|0|0|900|540|3|0|0|0|800|740|4|0|0|0|1560|540|4|0|0|0|1260|240|4|0|0|0|1260|540|4|0|0|0|1260|840|3|4|1|0|1135|240|4|0|0|0|1020|540|4|0|0|0|1120|740");
        Logger::getInstance()->debug("(Server:ProcessMessage) Encolando respuesta LoginOK.");

        unique_lock<mutex> lock(output_msg_mutex);

        this->outgoing_msg_queues[client->socket_id]->Append(login_response);

        output_msg_condition_variable.notify_all();

    }
    catch (AuthenticationException e)
    {
        Message* login_response = new Message("login-fail");
        Logger::getInstance()->debug("(Server:ProcessMessage) Encolando respuesta LoginFail.");
        this->outgoing_msg_queues[client->socket_id]->Append(login_response);
    }
    catch(MaxAllowedUsersException e)
    {
        Message* login_response = new Message("too-many-users");
        Logger::getInstance()->debug("(Server:ProcessMessage) Encolando respuesta TooManyUsers.");
        this->outgoing_msg_queues[client->socket_id]->Append(login_response);

        //TODO: mover esta logica a un metodo DisconnectClientSocket()
        this->clients.erase(client->socket_id);
        client->ShutDown();
        client->Close();
    }
}

void Server::HandleQuitRequest(ClientSocket* client, Message* message)
{
    Logger::getInstance()->debug("(Server:HandleQuitRequest) Procesando quit request.");
    QuitRequest* quit_request = new QuitRequest();
    message->GetDeserializedData(quit_request);
    this->game->DoQuit(quit_request);

    // Hack! estoy usando message_type: quit_request ya que falta definir quit_response.

    Logger::getInstance()->debug("(Server:HandleQuitRequest) Encolando respuesta logout");
    Message* quit_response= new Message("7|quit-ok");
    this->outgoing_msg_queues[client->socket_id]->Append(quit_response);


    Logger::getInstance()->debug("(Server:HandleQuitRequest) Cerrando clientsocket.");
    this->clients.erase(client->socket_id);
    client->ShutDown();
    client->Close();
    delete quit_request;
    delete quit_response;
}

void Server::HandleMoveRequest(ClientSocket* client, Message* message)
{
    Logger::getInstance()->debug("(Server:HandleMoveRequest) Procesando move request.");
    MoveRequest* move_request = new MoveRequest();
    message->GetDeserializedData(move_request);
    string game_serialize = this->game->DoMove(move_request, client->socket_id);
    Message* move_response = new Message(game_serialize);
    this->NotifyAll(move_response);
}

void Server::HandleRecoverBallRequest(ClientSocket* client, Message* message)
{
    Logger::getInstance()->debug("(Server:HandleRecoverBallRequest) Procesando recover ball request.");
    RecoverBallRequest* recover_ball_request = new RecoverBallRequest();
    message->GetDeserializedData(recover_ball_request);
    string game_serialize = this->game->DoRecoverBall(recover_ball_request, client->socket_id);
    Message* recover_ball_response = new Message(game_serialize);
    this->NotifyAll(recover_ball_response);
}

void Server::HandleKickRequest(ClientSocket* client, Message* message)
{
    Logger::getInstance()->debug("(Server:HandleKickRequest) Procesando kick request.");

    KickBallRequest* kick_ball_request = new KickBallRequest();
    message->GetDeserializedData(kick_ball_request);

    Message* game_serialized = new Message(this->game->DoKick(kick_ball_request, client->socket_id));

    this->NotifyAll(game_serialized);
}

void Server::HandlePassBallRequest(ClientSocket* client, Message* message)
{
    string client_id = to_string(client->socket_id);
    Logger::getInstance()->debug("(Server:HandlePassBallRequest) Procesando pass ball request. cliente: " + client_id);
    PassBallRequest* pass_ball_request = new PassBallRequest();
    message->GetDeserializedData(pass_ball_request);
    Message* response = this->game->DoPassBall(client, pass_ball_request);
    this->NotifyAll(response);
}

void Server::HandleChangePlayerRequest(ClientSocket* client, Message* message)
{
    string client_id = to_string(client->socket_id);
    Logger::getInstance()->debug("(Server:HandleChangePlayerRequest) Procesando change player request. cliente: " + client_id);
    ChangePlayerRequest* change_player_request = new ChangePlayerRequest();
    message->GetDeserializedData(change_player_request);
    Message* game_serialized = new Message(this->game->ChangePlayer(change_player_request, client->socket_id));
    this->NotifyAll(game_serialized);
}

void Server::SendMessage(ClientSocket* client)
{
    Logger::getInstance()->debug("(Server:SendMessage) Iniciando hilo para enviar mensajes a cliente: " + to_string(client->socket_id));
    Queue<Message>* outgoing_msg_queue = this->outgoing_msg_queues[client->socket_id];
    bool sending_msg = true; // Ver como desactivar y activar esto. (condition variables ??)
    while(sending_msg)
    {
        unique_lock<mutex> lock(output_msg_mutex);

        while(!outgoing_msg_queue->HasNext())
        {
            output_msg_condition_variable.wait(lock);
        }
        auto msg = outgoing_msg_queue->Next();
        Logger::getInstance()->debug("(Server:SendMessage) Enviando mensaje a cliente: " + to_string(client->socket_id));
        this->socket->Send(client, msg);
    }
}


void Server::NotifyAll(Message* message)
{
    Logger::getInstance()->debug("(Server:NotifyAll) Encolando mensaje para ser enviado a todos los clientes conectados.");

    unique_lock<mutex> lock(output_msg_mutex);

    auto it = this->outgoing_msg_queues.begin();
    while(it != this->outgoing_msg_queues.end())
    {
        Logger::getInstance()->debug("(Server:NotifyAll) Encolando mensaje para ser cliente: " + to_string(it->first));
        it->second->Append(message);
        it++;
    }
    output_msg_condition_variable.notify_all();
}
