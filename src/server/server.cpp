#include "server.h"

#include <chrono>
#include "../shared/network/exceptions/socket-connection-exception.h"
#include "session/authentication-exception.h"
#include "session/max-allowed-user-exception.h"
#include "session/invalid-team-exception.h"
#include "../shared/network/messages/quit-request.h"
#include "../shared/network/messages/pass-ball-request.h"
#include "game/non-existen-user-exception.h"

Server::Server(Configuration* config)
{
    Logger::getInstance()->info("Iniciando servidor en puerto:'"
                                + to_string(config->GetPort()) + "' y capacidad para '"
                                + to_string(config->GetMaxPlayers()) + "' usuarios.");

    this->message_queue = new Queue<pair<ClientSocket*, Message*>>();
    this->port = config->GetPort();
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
    bool binding_success = this->socket->Bind(this->port);
    if (binding_success) {
        this->socket->Listen(MAX_SOCKET_QUEUE_SIZE);

        this->ConnectingUsers();

        Logger::getInstance()->info("Comenzando el juego....'");
    }
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
        // Accept() bloquea el hilo hasta que un cliente intenta conectarse.
        ClientSocket* client = this->socket->Accept();

        unique_lock<mutex> lock(server_mutex);

        Logger::getInstance()->debug("(Server:ListenConnections) Agregando nuevo ClientSocket a colección de clientes.");
        this->clients[client->socket_id] = client;
        client_threads.push_back(thread(&Server::ReceiveMessages, this, client));

        SafeQueue<Message>* outgoing_msg_queue = new SafeQueue<Message>();
        this->outgoing_msg_queues[client->socket_id] = outgoing_msg_queue;
        // Disparo thread para envi ar mensajes a este ClienteSocket.
        thread outgoing_msg_thread(&Server::SendMessage, this, client);
        outgoing_msg_thread.detach();

        this->timers[client->socket_id] = std::chrono::system_clock::now();
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
            incoming_message = this->socket->Receive(client, 400);
            Logger::getInstance()->debug("(Server:ReceiveMessages) Mensaje recibido. Encolando para ser procesado.");
            // Aplico lock (mutex)  antes de enconlar el mensaje entrante.
            unique_lock<mutex> lock(input_msg_mutex);

            auto p_msg = make_pair(client, incoming_message);
            this->message_queue->Append(&p_msg);

            input_msg_condition_variable.notify_all();
        }
        catch (SocketConnectionException& e)
        {
            Logger::getInstance()->error("(Server:ReceiveMessages) Error de conexión. Cerrando socket cliente.");
            receiving_messages = false;
            this->DisconnectClient(client);
        }
    }
}

void Server::ProcessMessage(ClientSocket* client, Message* message)
{
    Logger::getInstance()->debug("(Server::ProcessMessage) Procesando mensaje. Tipo: " + to_string(message->GetType()));

    switch(message->GetType())
    {
    case MESSAGE_TYPE::HEALTH_CHECK:
        this->HandleHealthCheck(client, message);
        break;
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
    case MESSAGE_TYPE::PASS_REQUEST:
        this->HandlePassBallRequest(client, message);
        break;
    case MESSAGE_TYPE::CHANGE_FORMATION_REQUEST:
        this->HandleChangeFormationRequest(client, message);
        break;
    case MESSAGE_TYPE::LONG_PASS_REQUEST:
        this->HandleLongPassRequest(client, message);
        break;
    default:
        Logger::getInstance()->error("(Server::ProcessMessage) No hay handler para este tipo de mensaje.");
    }
}

void Server::RestartTimers() {

    auto it = this->timers.begin();
    while(it != this->timers.end())
    {
        it->second = std::chrono::system_clock::now();
        it++;
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
        Message* login_response;
        if (!this->game->IsRunning() && this->game->GetTeamUsersNum(login_request.GetTeam()) == 1) {
            //Como es el primero del equipo elige formacion
            login_response = new Message("choose-formation");
            Logger::getInstance()->debug("(Server:ProcessMessage) Encolando respuesta: choose-formation");
        }
        else {
            login_response = new Message("login-ok");
            Logger::getInstance()->debug("(Server:ProcessMessage) Encolando respuesta: login-ok");
        }

        this->socket->Send(client, login_response);

        // Si ya se loguearon todos, se notifica a todos los usuarios para empezar a jugar.
        if (!this->game->IsRunning() && this->game->IsReadyToStart()) {
            this->StartGame();
        }
    }
    catch (AuthenticationException& e)
    {
        Message* login_response = new Message("login-fail");
        Logger::getInstance()->debug("(Server:ProcessMessage) Encolando respuesta LoginFail.");
        this->outgoing_msg_queues[client->socket_id]->Append(login_response);
    }
    catch(MaxAllowedUsersException& e)
    {
        Message* login_response = new Message("too-many-users");
        Logger::getInstance()->debug("(Server:ProcessMessage) Encolando respuesta TooManyUsers.");
        this->outgoing_msg_queues[client->socket_id]->Append(login_response);
    }
    catch (InvalidTeamException& e)
    {
        Message* login_response = new Message("invalid-team");
        Logger::getInstance()->debug("(Server:ProcessMessage) Encolando respuesta InvalidTeam.");
        this->outgoing_msg_queues[client->socket_id]->Append(login_response);
    }
    catch (NonExistentUserException& e)
    {
        Message* login_response = new Message("non-existent-user");
        Logger::getInstance()->debug("(Server:ProcessMessage) Encolando respuesta el usuario no esta en la partida.");
        this->outgoing_msg_queues[client->socket_id]->Append(login_response);
    }
}

void Server::StartGame() {
    this->RestartTimers();
    this->game->StartGame();

    // Disparo thread para notificar game-state periodicamente.
    std::thread game_state_notifier_thread(&Server::NotifyGameState, this);
    game_state_notifier_thread.detach();
}

void Server::HandleQuitRequest(ClientSocket* client, Message* message)
{
	string client_id = to_string(client->socket_id);
    Logger::getInstance()->debug("(Server:HandleQuitRequest) Procesando quit request. Client: " + client_id);
    QuitRequest* quit_request = new QuitRequest();
    message->GetDeserializedData(quit_request);
    this->game->DoQuit(client);

    // NO se manda mensaje de logout para evitar problemas.

    Logger::getInstance()->debug("(Server:HandleQuitRequest) Cerrando clientsocket: " + client_id);
    this->clients.erase(client->socket_id);
    client->ShutDown();
    client->Close();
    delete quit_request;
}

void Server::HandleMoveRequest(ClientSocket* client, Message* message)
{
    Logger::getInstance()->debug("(Server:HandleMoveRequest) Procesando move request.");
    MoveRequest* move_request = new MoveRequest();
    message->GetDeserializedData(move_request);
    this->game->DoMove(move_request, client->socket_id);
}

void Server::HandleRecoverBallRequest(ClientSocket* client, Message* message)
{
    Logger::getInstance()->debug("(Server:HandleRecoverBallRequest) Procesando recover ball request.");
    RecoverBallRequest* recover_ball_request = new RecoverBallRequest();
    message->GetDeserializedData(recover_ball_request);
    this->game->DoRecoverBall(recover_ball_request, client->socket_id);
}

void Server::HandleKickRequest(ClientSocket* client, Message* message)
{
    Logger::getInstance()->debug("(Server:HandleKickRequest) Procesando kick request.");

    KickBallRequest* kick_ball_request = new KickBallRequest();
    message->GetDeserializedData(kick_ball_request);
    this->game->DoKick(kick_ball_request, client->socket_id);
}

void Server::HandleLongPassRequest(ClientSocket* client, Message* message)
{
    Logger::getInstance()->debug("(Server:HandleLongPassRequest) Procesando long pass request.");

    LongPassRequest* long_pass_request = new LongPassRequest();
    message->GetDeserializedData(long_pass_request);
    this->game->DoLongPass(long_pass_request, client->socket_id);
}

void Server::HandlePassBallRequest(ClientSocket* client, Message* message)
{
    string client_id = to_string(client->socket_id);
    Logger::getInstance()->debug("(Server:HandlePassBallRequest) Procesando pass ball request. cliente: " + client_id);
    PassBallRequest* pass_ball_request = new PassBallRequest();
    message->GetDeserializedData(pass_ball_request);
    this->game->DoPassBall(client, pass_ball_request);
}

void Server::HandleChangePlayerRequest(ClientSocket* client, Message* message)
{
    string client_id = to_string(client->socket_id);
    Logger::getInstance()->debug("(Server:HandleChangePlayerRequest) Procesando change player request. cliente: " + client_id);
    ChangePlayerRequest* change_player_request = new ChangePlayerRequest();
    message->GetDeserializedData(change_player_request);
    this->game->ChangePlayer(change_player_request, client->socket_id);
}

void Server::SendMessage(ClientSocket* client)
{
    Logger::getInstance()->debug("(Server:SendMessage) Iniciando hilo para enviar mensajes a cliente: " + to_string(client->socket_id));
    SafeQueue<Message>* outgoing_msg_queue = this->outgoing_msg_queues[client->socket_id];
    bool sending_msg = outgoing_msg_queue != NULL; // Ver como desactivar y activar esto. (condition variables ??)

    while(sending_msg)
    {
        if(outgoing_msg_queue->HasNext())
        {
            auto msg = outgoing_msg_queue->Next();
            Logger::getInstance()->debug("(Server:SendMessage) Enviando mensaje a cliente: " + to_string(client->socket_id));
            this->socket->Send(client, msg);
        }
    }
}


void Server::NotifyAll(Message* message)
{
    Logger::getInstance()->debug("(Server:NotifyAll) Encolando mensaje para ser enviado a todos los clientes conectados.");

    auto it = this->outgoing_msg_queues.begin();
    while(it != this->outgoing_msg_queues.end())
    {
        /*
        * Se instancia una copia de Message para c/client para poder hacer delete en el scope del método SocketServer:Send();
        */
        Message* per_client_copy_msg = new Message(string(message->GetData()));
        Logger::getInstance()->debug("(Server:NotifyAll) Encolando mensaje para ser cliente: " + to_string(it->first));
        it->second->Append(per_client_copy_msg);
        it++;
    }

    delete message;
}

void Server::NotifyGameState()
{
    IdGenerator id_generator;
    while(this->game->IsRunning())
    {
        this->CheckDisconnections();
        Logger::getInstance()->debug("(Server:NotifyGameState) Enviando game state a todos los clientes.");
        string state_id = id_generator.GetNext();
        Message* game_state_msg = new Message(this->game->GetGameState()->GetMatch()->Serialize() + "|" + state_id);
        this->NotifyAll(game_state_msg);

        std::this_thread::sleep_for(std::chrono::milliseconds(SEND_GAME_STATE_EVERY_MILLISECONDS));

        unique_lock<mutex> lock(input_msg_mutex); // agrego mutex para sincronizar hilos y ver si soluciona el seg-fault del infierno
        this->game->Run();
    }
}


void Server::DisconnectClient(ClientSocket* client)
{
    this->game->DisconnectClient(client);

    // TODO ver si hay que hacer delete la cola que se elimino del mapa
    this->outgoing_msg_queues.erase(client->socket_id);
    this->clients.erase(client->socket_id);
    client->ShutDown();
    client->Close();
}

void Server::HandleHealthCheck(ClientSocket* client, Message* message)
{
    string socket_id = to_string(client->socket_id);
    Logger::getInstance()->debug("(Server:HandleHealthCheck) Sigue vivo el cliente: " + socket_id);
    this->timers[client->socket_id] = std::chrono::system_clock::now();
}

void Server::HandleChangeFormationRequest(ClientSocket* client, Message* message)
{
    string socket_id = to_string(client->socket_id);
    ChangeFormationRequest cfRequest;
    message->GetDeserializedData(&cfRequest);
    this->game->ChangeFormation(&cfRequest, client->socket_id);

    Logger::getInstance()->debug("(Server::HandleChangeFormationRequest) Procesado el cambio de formacion hecho por " + to_string(client->socket_id) + ". Verificando si el juego esta listo para comenzar..");
    //Los otros jugadores pueden estar esperando que algun usuario elija una formacion para su equipo, por lo tanto verifico si debo empezar el juego o no
    if (!this->game->IsRunning() && this->game->IsReadyToStart()) {
        this->StartGame();
    }
}

void Server::CheckDisconnections()
{
    Logger::getInstance()->debug("(Server::CheckDisconnections)");
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

    auto it = this->timers.begin();
    while(it != this->timers.end())
    {
        unsigned int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>
                             (now - it->second).count();
        if (elapsed_millis > CONNECTION_TIMEOUT) {
            if (this->clients.find(it->first) != this->clients.end()) {
                Logger::getInstance()->debug("(Server::CheckDisconnections) Desconectando client " + to_string((int)it->first));
                this->DisconnectClient(this->clients[it->first]);
                Logger::getInstance()->debug("(Server::CheckDisconnections) Cliente " + to_string((int)it->first) + " desconectado");
            }
        }
        it++;
    }
}
