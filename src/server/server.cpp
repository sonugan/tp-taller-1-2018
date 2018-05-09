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

}

Server::~Server()
{
    delete this->requests_queue;
    delete this->clients;
    delete this->socket;
}

void Server::Init()
{
    this->socket->Bind(config->GetPort());
    this->socket->Listen(MAX_SOCKET_QUEUE_SIZE);

    Logger::getInstance()->info("Escuchando conexiones....'");
    cout << "escuchando conexiones...." << "\n";

    this->ConnectingUsers();

    Logger::getInstance()->info("comenzando el juego....'");
    cout << "jugando!" << "\n";

    this->socket->Close();

    Logger::getInstance()->info("cerrando el servidor....'");
}

void Server::ConnectingUsers()
{
    this->connected_user_count = 0;
    thread wait_connections_thread(&Server::ListenConnections, this);

    while(!this->ReadyToStart()) {}

    pthread_cancel(wait_connections_thread.native_handle());
    wait_connections_thread.join();
}

void Server::ListenConnections()
{
    vector<thread*> client_threads;
    while(!this->ReadyToStart())
    {
        ClientSocket* client = this->socket->Accept();
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
    bool success_login = false;
    while(!this->ReadyToStart() || success_login)
    {
        Message incommingMessage1 = this->socket->Receive(client,255);
        Login* l = new Login();
        ISerializable* data = incommingMessage1.GetDeserializedData(l);
        if(this->config->IsValidCredential(l->GetUsername(), l->GetPassword()))
        {
            cout << "Se conectó: " << l->GetUsername() << "\n";
            Logger::getInstance()->info("inició sesión el usuario:'" + l->GetUsername() + ".");
            Request login_state_request("ok");
            this->socket->Send(client, login_state_request);
            this->connected_user_count++;
            success_login = true;
        }
        else
        {
            Logger::getInstance()->info("Usuario o contraseña inválidos:'" + l->GetUsername() + ".");
            cout << "Usuario o contraseña inválidos: " << l->GetUsername() << "\n";
            Request login_state_request("fail");
            this->socket->Send(client, login_state_request);
        }
    }
}
