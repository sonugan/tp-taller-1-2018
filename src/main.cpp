#include "game/game.h"
#include "configuration-parser.h"


int main( int argc, char* args[] ) {

    ConfigurationParser* parser = new ConfigurationParser();
    parser->ReadFile("aaa");

    Game* game = new Game();
    game->Start();
    game->End();
	return 0;
}
