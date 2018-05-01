#include "client/game.h"
#include "shared/configuration/cli-options-parser.h"
#include "shared/configuration/cli-options.h"
#include "shared/configuration/configuration.h"
//Descomentame para probar sockets
#include "shared/network/server-socket.h"
#include "shared/network/client-socket.h"
#include "shared/network/socket-address.h"
#include "shared/network/message.h"


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

//    Configuration* config = new Configuration();
//    load_configuration(argc, args, config);
//    Logger::getInstance()->setMode(config->GetLogLevel());
//
//    Game* game = new Game(config);
//    game->Start();
//    game->End();
//    delete game;
//    delete config;

//  Descomentame para probar sockets
    if(string(args[1]) =="s")
    {
        cout << "iniciando....." << "\n";
        ServerSocket serverSocket;
        SocketAddress address(51717);
        serverSocket.Bind(address);
        serverSocket.Listen(5);
        ServerSocket clientSocket = serverSocket.Accept();
        //printf("server: got connection from %s port %d\n",
        //inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
        Message m("Hello, world!\n", 13);
        serverSocket.Write(clientSocket, m);

        Message incommingMessage = serverSocket.Read(clientSocket,255);
        printf("Here is the message: %s\n",incommingMessage.GetData());
        serverSocket.Close();
    }
    else
    {
        ClientSocket clientSocket;
        SocketAddress address(51717, "localhost");
        clientSocket.Connect(address);

        printf("Please enter the message: ");
        char buffer[256];
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        //Message m("Hello, dlrow!\n", 13);
        Message m("Hello, dlrow!\n");
        clientSocket.Write(clientSocket, m);
        //n = write(sockfd, buffer, strlen(buffer));

        clientSocket.Close();
    }
	return 0;
}
