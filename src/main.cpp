#include "client/game.h"
#include "server/server.h"
#include "shared/configuration/cli-options-parser.h"
#include "shared/configuration/cli-options.h"
#include "shared/configuration/configuration.h"

#include <iostream>

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

    Configuration* config = new Configuration();
    load_configuration(argc, args, config);
    Logger::getInstance()->setMode(config->GetLogLevel());

    bool isClient = config->InitModeIsClient();

    // Para las pruebas, esto se deberia cargar con lo que venga del login
    string username = "user";
    string password = "1234";

    if (isClient) {

        if (config->IsValidCredential(username, password))
        {
            // POR AHORA QUEDA IGUAL A LO QUE YA TENIAMOS
            Game* game = new Game(config);
            game->Start();
            game->End();
            delete game;
            delete config;
        }
        else
        {
            Logger::getInstance()->error("El usuario " + username + " o la password " + password + " son incorrectos.");
        }

    } else { // SE INICIO COMO SERVER
        Server* server = new Server();
        server->InitServer();
        delete server;
    }

	return 0;
}
