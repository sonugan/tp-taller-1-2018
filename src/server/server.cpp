#include "server.h"

#include "../shared/network/exceptions/socket-connection-exception.h"
#include "session/authentication-exception.h"

Server::Server(Configuration* config)
{
    Logger::getInstance()->info("Iniciando servidor en puerto:'"
                                + to_string(config->GetPort()) + "' y capacidad para '"
                                + to_string(config->GetMaxPlayers()) + "' usuarios.");

    this->clients = new Queue<ClientSocket>();
    this->message_queue = new Queue<pair<ClientSocket*, Message*>>();
    this->port = config->GetPort();
    this->user_count = config->GetMaxPlayers();
    this->socket = new ServerSocket();
    this->session_manager = new SessionManager(config->GetCredentials());
}

Server::~Server()
{
    delete this->message_queue;
    delete this->clients;
    delete this->socket;
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

void Server::ConnectingUsers()
{
    this->connected_user_count = 0;
    thread wait_connections_thread(&Server::ListenConnections, this);


    while(!this->ReadyToStart())
    {
        // TODO: pensar bien donde meter esto!
        while(this->message_queue->HasNext())
        {
            Logger::getInstance()->debug("(Server:ConnectingUsers) Desencolando mensaje para procesar");
            unique_lock<mutex> lock(server_mutex);
            auto msg = this->message_queue->Next();
            ClientSocket* client = msg->first;
            Message* message = msg->second;
            this->ProcessMessage(client, message);
        }
    }

    pthread_cancel(wait_connections_thread.native_handle());
    wait_connections_thread.join();
}

void Server::ListenConnections()
{
    Logger::getInstance()->debug("(Server:ListenConnections) Escuchando conexiones....'");
    vector<thread*> client_threads;
    while(!this->ReadyToStart())
    {
        Logger::getInstance()->debug("(Server:ListenConnections) Previo Accept().");
        ClientSocket* client = this->socket->Accept();
        Logger::getInstance()->debug("(Server:ListenConnections) Agregando nuevo ClientSocket a colección de clientes.");
        this->clients->Append(client);
        client_threads.push_back(new thread(&Server::ReceiveMessages, this, client));
    }
}

bool Server::ReadyToStart()
{
    return this->connected_user_count == user_count;
}

void Server::ReceiveMessages(ClientSocket* client)
{
    Logger::getInstance()->debug("(Server:ReceiveMessages) Iniciando hilo receptor de mensajes.");
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
            unique_lock<mutex> lock(server_mutex);
            auto p_msg = make_pair(client, incoming_message);
            this->message_queue->Append(&p_msg);
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
    //TODO: por ahora solo procesa mensajes de login.
    Logger::getInstance()->debug("(Server::ProcessMessage) Procesando mensaje.");
    Login* login_request = new Login();
    message->GetDeserializedData(login_request);

    try
    {
        User* autheticated_user = this->session_manager->Authenticate(login_request);
        // este contador tal vez no debería estar en el server sino en el game.
        this->connected_user_count++;
        // aca deberiamos hacer algo asi
        //game->AddNewUser(autheticated_user);
        Message* login_response = new Message("login-ok");
        Logger::getInstance()->debug("(Server:ProcessMessage) Enviando respuesta LoginOK.");
        this->socket->Send(client, login_response);
    }
    catch (AuthenticationException e)
    {
        Message* login_response = new Message("login-fail");
        Logger::getInstance()->debug("(Server:ProcessMessage) Enviando respuesta LoginFail.");
        this->socket->Send(client, login_response);
    }
}
