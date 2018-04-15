#include "game/game.h"
#include "configuration/cli-options-parser.h"
#include "configuration/cli-options.h"
#include "configuration/configuration.h"

#include <iostream>

void loadConfiguration(int argc, char* args[], Configuration* config)
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
    loadConfiguration(argc, args, config);
    std::cout << config->GetSpritesPath() << "\n";
    std::cout << config->GetLogLevel() << "\n";
    std::cout << config->GetFormation() << "\n";
    std::cout << config->GetTeamName() << "\n";
    std::cout << config->GetShirt() << "\n";

    Game* game = new Game(config);
    game->Start();
    game->End();
    delete game;
    delete config;
	return 0;
}
