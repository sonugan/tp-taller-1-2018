#include "game-controller.h"

GameController::GameController(Game* game, Client* client) {
    this->game = game;
    this->client = client;
}

GameController::~GameController() {
    //dtor
}

void GameController::ExitGame(const Uint8 *keyboard_state_array) {
    if (keyboard_state_array[SDL_SCANCODE_ESCAPE]) {
		if (client->IsConnected())
		{
			QuitRequest* quit_request = new QuitRequest(game->GetUser()->GetUsername());
			client->Quit(quit_request);
		}
    }
}

void GameController::Handle(const Uint8* keyboard_state_array) {
    ExitGame(keyboard_state_array);
}


