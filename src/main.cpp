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
    Server* server = new Server(2, config);//TODO: levantar puerto de configuracion o de consola
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
        SocketAddress address(51717, "localhost");
        clientSocket.Connect(address);

        printf("Escribí algo: ");
        char buffer[256];
        bzero(buffer,256);
        fgets(buffer,255,stdin);

        string s = string(buffer);
        //Request r(s);
        Login l("gperez", "123456");
        //Request r(&l);
        Request r(l.Serialize());
        clientSocket.Send(r);

        clientSocket.Close();
    }
    else
    {
        InitServer(argc, args, config);
    }
    delete config;
	return 0;
}
