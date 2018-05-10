#include "server.h"

Server::Server(Configuration* config)
{
    Logger::getInstance()->info("iniciando servidor en puerto:'"
                                + to_string(config->GetPort()) + "' y capacidad para '"
                                + to_string(config->GetMaxPlayers()) + "' usuarios.");

    this->clients = new Queue<ClientSocket>();
    this->requests_queue = new Queue<Message>();
    this->port = config->GetPort();
    this->user_count = config->GetMaxPlayers();
    this->credentials = config->GetCredentials();
    this->socket = new ServerSocket();
}

Server::~Server()
{
    delete this->requests_queue;
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
        // Y este loop para que es??
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
        client_threads.push_back(new thread(&Server::ManageLoginRequests, this, client));
    }
}

bool Server::ReadyToStart()
{
    return this->connected_user_count == user_count;
}

void Server::ManageLoginRequests(ClientSocket* client)
{
    Logger::getInstance()->debug("(Server:ManageLoginRequests) Iniciando Login thread.");
    bool success_login = false;
    while(!this->ReadyToStart() || success_login)
    {
        Logger::getInstance()->debug("(Server:ManageLoginRequests) Esperando login request.");
        Message incommingMessage1 = this->socket->Receive(client, 255);
        Login* l = new Login();
        ISerializable* data = incommingMessage1.GetDeserializedData(l);
        if(this->IsValidUser(l->GetUsername(), l->GetPassword()))
        {
            Logger::getInstance()->info("Usuario válido. Se conectó: " + l->GetUsername());

            Request login_state_request("ok");
            Logger::getInstance()->debug("(Server:ManageLoginRequests) Enviando respuesta LoginOK.");
            this->socket->Send(client, login_state_request);
            this->connected_user_count++;
            success_login = true;
        }
        else
        {
            Logger::getInstance()->info("Usuario o contraseña inválidos:'" + l->GetUsername() + ".");
            Request login_state_request("fail");
            Logger::getInstance()->debug("(Server:ManageLoginRequests) Enviando respuesta LoginFail.");
            this->socket->Send(client, login_state_request);
        }
    }
}

bool Server::IsValidUser(string username, string password)
{
    map<string,string>::iterator it = this->credentials.find(username);

    if (it != this->credentials.end())
    {
        // Encontro el usuario, comparo las passwords
        string stored_password = it->second;
        return stored_password.compare(password) == 0;
    }

    return false; // No existe ese usuario
}
