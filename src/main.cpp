#include "game/game.h"
#include "configuration.h"
#include "configuration/cli-options-parser.h"

#include <iostream>
#include <string>

Configuration* loadConfiguration(int argc, char* args[])
{
    CLIOptionsParser* parser = new CLIOptionsParser();
    std::string config_path = parser->GetConfigPath(argc, args);
    std::string log_level = parser->GetLogLevel(argc, args);
    return Configuration::Load(config_path, log_level);
}

int main( int argc, char* args[] ) {

    Configuration* config = loadConfiguration(argc, args);
    std::cout << config->GetSpritesPath() << "\n";
    std::cout << config->GetLogLevel() << "\n";
    std::cout << config->GetFormation() << "\n";

    Game* game = new Game();
    game->Start();
    game->End();
	return 0;
}
