#include "server.h"

Server::Server(u_int user_count, Configuration* config)
{
    this->requests_queue = new MessageQueue();

    this->user_count = user_count;
    this->config = config;

    //SocketAddress address(config->GetPort());
    this->socket = new ServerSocket();
    this->socket->Bind(config->GetPort());
    this->socket->Listen(MAX_SOCKET_QUEUE_SIZE);

    cout << "escuchando conexiones...." << "\n";

    this->ConnectingUsers();

    cout << "jugando!" << "\n";
}

Server::~Server()
{
    delete this->requests_queue;
    delete this->socket;
}

void Server::InitServer()
{

}

void Server::ConnectingUsers()
{
    this->clients_count = 0;
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
        this->clients.push_back(this->socket->Accept());
    }
}

bool Server::ReadyToStart()
{
    return this->clients_count == user_count;
}

void Server::ManageClientConnections()
{
    vector<thread*> client_threads;
    while(!this->ReadyToStart())
    {
        if(this->clients.size() > 0)
        {
            ClientSocket client = this->clients.front();
            this->clients.pop_back();
            client_threads.push_back(new thread(&Server::ManageClientConnection, this, client));
        }
    }
}

void Server::ManageClientConnection(ClientSocket client)
{
    Message incommingMessage1 = this->socket->Receive(client,255);
    Login* l = new Login();
    ISerializable* data = incommingMessage1.GetDeserializedData(l);
    cout << "Mensaje del cliente: " << l->GetUsername() << "\n";
    this->clients_count++;
}
