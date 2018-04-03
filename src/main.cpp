#include "game/game.h"
#include "configuration/configuration-parser.h"
#include "configuration.h"

#include <iostream>

int main( int argc, char* args[] ) {

    ConfigurationParser* parser = new ConfigurationParser();
    Configuration config = parser->ReadFile("aaa");
    std::cout << config.GetLogLevel() << "\n";

    Game* game = new Game();
    game->Start();
    game->End();
	return 0;
}
