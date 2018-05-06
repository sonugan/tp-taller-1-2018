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
#include "shared/network/iserializable.h"
#include "shared/network/login.cpp"
#include "shared/utils/string-utils.h"


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

void InitServer(int argc, char* args[], Configuration* config)
{
    Server* server = new Server(config);
    server->InitServer();
    delete server;
}

int main( int argc, char* args[] ) {

    Configuration* config = new Configuration();
    load_configuration(argc, args, config);
    Logger::getInstance()->setMode(config->GetLogLevel());

    bool isClient = config->InitModeIsClient();

    if (isClient) {

        // POR AHORA QUEDA IGUAL A LO QUE YA TENIAMOS
        /*Game* game = new Game(config);
        if (game->IsCorrectlyInitialized())
        {
            game->Start();
            game->End();
        }
        delete game;*/

        ClientSocket clientSocket;
        SocketAddress address(config->GetPort(), config->GetServerHostname().c_str());
        //SocketAddress address(51717, "localhost");
        clientSocket.Connect(address);

        bool is_logued = false;
        do {
            printf("Escribí tu usuario: ");
            char buffer[256];
            bzero(buffer,256);
            fgets(buffer,255,stdin);

            string username = string(buffer);
            username = StringUtils::RemoveLastNewLine(username);

            printf("Escribí tu password: ");
            bzero(buffer,256);
            fgets(buffer,255,stdin);

            string password = string(buffer);
            password = StringUtils::RemoveLastNewLine(password);
            //Request r(s);
            Login l(username, password);
            //Request r(&l);
            Request r(l.Serialize());
            clientSocket.Send(r);

            Message login_status = clientSocket.Receive(255);
            cout << login_status.GetData() << "\n";
            if(login_status.GetData() == "ok")
            {
                is_logued = true;
            }
        } while(!is_logued);

        clientSocket.Close();
    }
    else
    {
        InitServer(argc, args, config);
    }
    delete config;
	return 0;
}
