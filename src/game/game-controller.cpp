#include "game-controller.h"

GameController::GameController(Game* game) {
    this->game = game;
}

GameController::~GameController() {
    //dtor
}

void GameController::ExitGame(const Uint8 *keyboard_state_array) {
    if (keyboard_state_array[SDL_SCANCODE_ESCAPE]) {
        this->game->RequestQuit();
    }
}

void GameController::Handle(const Uint8* keyboard_state_array) {
    ExitGame(keyboard_state_array);
}
