#include "client/game.h"
#include "server/server.h"
#include "shared/configuration/cli-options-parser.h"
#include "shared/configuration/cli-options.h"
#include "shared/configuration/configuration.h"
//Descomentame para probar sockets
#include "shared/network/server-socket.h"
#include "shared/network/client-socket.h"
#include "shared/network/socket-address.h"
#include "shared/network/message.h"
#include "shared/network/request.h"


#include <iostream>
#include <string.h>

void load_configuration(int argc, char* args[], Configuration* config)
{
    CLIOptionsParser* parser = new CLIOptionsParser();
    string config_path = parser->GetConfigPath(argc, args);
    string log_level = parser->GetLogLevel(argc, args);
    CLIOptions* cli_options = new CLIOptions(config_path, log_level);
    Configuration::Load(config, cli_options->GetConfigPath(), cli_options->GetLogLevel());
    delete parser;
    delete cli_options;
}

int main( int argc, char* args[] ) {
/*
    Configuration* config = new Configuration();
    load_configuration(argc, args, config);
    Logger::getInstance()->setMode(config->GetLogLevel());

    bool isClient = config->InitModeIsClient();
*/
    bool isClient = true;
    if(string(args[1]) == "-server")
    {
        isClient = false;
    }

    if (isClient) {

        // POR AHORA QUEDA IGUAL A LO QUE YA TENIAMOS
        /*Game* game = new Game(config);
        if (game->IsCorrectlyInitialized())
        {
            game->Start();
            game->End();
        }
        delete game;*/

    } else { // SE INICIO COMO SERVER
        Server* server = new Server(51717, 2);//TODO: levantar puerto de configuracion o de consola
        server->InitServer();
        delete server;
    }

    //delete config;

  //Descomentame para probar sockets
    /*if(string(args[1]) =="s")
    {
        cout << "iniciando....." << "\n";
        ServerSocket serverSocket;
        SocketAddress address(51717);
        serverSocket.Bind(address);
        serverSocket.Listen(5);
        ServerSocket clientSocket1 = serverSocket.Accept();
        //printf("server: got connection from %s port %d\n",
        //inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
        //Message m("Hello, world!\n", 13);
        Request r("Te conectaste!\n");
        serverSocket.Send(clientSocket1, r);

        Message incommingMessage1 = serverSocket.Receive(clientSocket1,255);
        printf("Mensaje del cliente: %s\n",incommingMessage1.GetData());

        serverSocket.Close();
    }
    else
    {*/
    if(string(args[1]) =="c")
    {
        ClientSocket clientSocket;
        SocketAddress address(51717, "localhost");
        clientSocket.Connect(address);

        //Message m = clientSocket.Receive(15);
        //printf("Mensaje del servidor: %s\n",m.GetData());

        printf("Escribí algo: ");
        char buffer[256];
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        //Message m("Hello, dlrow!\n", 13);
        //Message m("Hello, dlrow!\n");
        string s = string(buffer);
        Request r(s);
        clientSocket.Send(r);
        //n = write(sockfd, buffer, strlen(buffer));
        clientSocket.Close();
    }
	return 0;
}
