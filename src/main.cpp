#include "game/game.h"
#include "configuration/configuration-parser.h"
#include "configuration.h"

#include <iostream>
#include <string>

// Estos métodos podrían ser parte de un CliParser
std::string getConfigPath(int argc, char* args[])
{
    //TODO: Implementar!
    return "";
}

std::string getLogLevel(int argc, char* args[])
{
    //TODO: Implementar!
    return "";
}

Configuration* loadConfiguration(int argc, char* args[])
{
    std::string config_path = getConfigPath(argc, args);
    std::string log_level = getLogLevel(argc, args);
    return Configuration::Load(config_path, log_level);
}

int main( int argc, char* args[] ) {

    Configuration* config = loadConfiguration(argc, args);
    std::cout << config->GetSpritesPath() << "\n";

    Game* game = new Game();
    game->Start();
    game->End();
	return 0;
}
