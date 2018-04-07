#include "game/game.h"
#include "configuration.h"
#include "cli-options.h"

#include <iostream>

Configuration* loadConfiguration(int argc, char* args[])
{
    CLIOptions* cli_options = CLIOptions::GetOptions(argc, args);
    return Configuration::Load(cli_options->GetConfigPath(), cli_options->GetLogLevel());
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
