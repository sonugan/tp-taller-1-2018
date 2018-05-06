#include "server.h"

Server::Server(Configuration* config)
{
    Logger::getInstance()->info("iniciando servidor en puerto:'"
        + to_string(config->GetPort()) + "' y capacidad para '"
        + to_string(config->GetMaxPlayers()) + "' usuarios.");

    this->clients = new Queue<ClientSocket>();
    this->requests_queue = new Queue<Message>();

    this->config = config;
    this->user_count = this->config->GetMaxPlayers();

    this->socket = new ServerSocket();
    this->socket->Bind(config->GetPort());
    this->socket->Listen(MAX_SOCKET_QUEUE_SIZE);

    Logger::getInstance()->info("escuchando conexiones....'");
    cout << "escuchando conexiones...." << "\n";

    this->ConnectingUsers();

    Logger::getInstance()->info("comenzando el juego....'");
    cout << "jugando!" << "\n";

    this->socket->Close();

    Logger::getInstance()->info("cerrando el servidor....'");
}

Server::~Server()
{
    delete this->requests_queue;
    delete this->clients;
    delete this->socket;
}

void Server::InitServer()
{

}

void Server::ConnectingUsers()
{
    this->connected_user_count = 0;
    thread wait_connections_thread(&Server::ListenConnections, this);
    thread attend_connections_thread(&Server::ManageClientConnections, this);

    while(!this->ReadyToStart()){}

    pthread_cancel(wait_connections_thread.native_handle());
    pthread_cancel(attend_connections_thread.native_handle());
    wait_connections_thread.join();
    attend_connections_thread.join();
}

void Server::ListenConnections()
{
    vector<thread*> client_threads;
    while(!this->ReadyToStart())
    {
        //this->clients.push_back(this->socket->Accept());
        this->clients->Append(this->socket->Accept());
    }
}

bool Server::ReadyToStart()
{
    return this->connected_user_count == user_count;
}

void Server::ManageClientConnections()
{
    vector<thread*> client_threads;
    while(!this->ReadyToStart())
    {
        if(this->clients->HasNext())
        {
            ClientSocket* client = this->clients->Next();
            client_threads.push_back(new thread(&Server::ManageClientConnection, this, client));
        }
        /*if(this->clients.size() > 0)
        {
            ClientSocket client = this->clients.front();
            this->clients.pop_back();
            client_threads.push_back(new thread(&Server::ManageClientConnection, this, client));
        }*/
    }
}

void Server::ManageClientConnection(ClientSocket* client)
{
    Message incommingMessage1 = this->socket->Receive(client,255);
    Login* l = new Login();
    ISerializable* data = incommingMessage1.GetDeserializedData(l);
    if(this->config->IsValidCredential(l->GetUsername(), l->GetPassword()))
    {
        cout << "Se conectó: " << l->GetUsername() << "\n";
        Logger::getInstance()->info("inició sesión el usuario:'" + l->GetUsername() + ".");
        this->connected_user_count++;
    }
    else
    {
        Logger::getInstance()->info("Usuario o contraseña inválidos:'" + l->GetUsername() + ".");
        cout << "Usuario o contraseña inválidos: " << l->GetUsername() << "\n";
    }
}
