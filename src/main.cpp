#include "game/game.h"

int main( int argc, char* args[] ) {
    Game* game = new Game();
    game->Start();
    game->End();
	return 0;
}
