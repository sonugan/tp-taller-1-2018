#include "client/game.h"
#include "server/server.h"
#include "shared/configuration/cli-options-parser.h"
#include "shared/configuration/cli-options.h"
#include "shared/configuration/configuration.h"
#include "client.h"


#include <iostream>
#include <string.h>

void load_configuration(int argc, char* args[], Configuration* config)
{
    //TODO: ajustar option mode=client/server. AUN NO FUNCIONA BIEN!!
    CLIOptionsParser* parser = new CLIOptionsParser();
    string config_path = parser->GetConfigPath(argc, args);
    string log_level = parser->GetLogLevel(argc, args);
    string mode = parser->GetMode(argc, args);
    CLIOptions* cli_options = new CLIOptions(config_path, log_level, mode);
    Configuration::Load(config, cli_options->GetConfigPath(), cli_options->GetLogLevel(), cli_options->GetMode());
    delete parser;
    delete cli_options;
}

void InitServer(int argc, char* args[], Configuration* config)
{
    Server* server = new Server(config);
    server->Init();
    delete server;
}

int main( int argc, char* args[] ) {

    Configuration* config = new Configuration();
    load_configuration(argc, args, config);
    Logger::getInstance()->setLogLevel(config->GetLogLevel());

    bool isClient = config->InitModeIsClient();

    if (isClient) {

        // POR AHORA QUEDA IGUAL A LO QUE YA TENIAMOS
        Game* game = new Game(config);
        if (game->IsCorrectlyInitialized())
        {
            game->Start();
            game->End();
        }
        delete game;

    }
    else
    {
        InitServer(argc, args, config);
    }
    delete config;
	return 0;
}
