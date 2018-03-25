#include "game.h"
#include <iostream>

Game::Game()
{
    CreateModel();
    CreateViews();
}

Game::~Game()
{
    DestroyModel();
    DestroyViews();
}

void Game::Start()
{
    std::cout << "Start game..." << "\n";
}

void Game::CreateModel() {
    std::cout << "Creando modelo..." << "\n";
    this->pitch = new Pitch();
    this->player = new Player();
}

void Game::CreateViews() {
    std::cout << "Creando vistas..." << "\n";
    this->pitch_view = new PitchView(this->pitch);


}

void Game::DestroyModel() {
    std::cout << "Destruyendo modelo..." << "\n";
    delete this->pitch;
    delete this->player;
}

void Game::DestroyViews() {
    std::cout << "Destruyendo vistas..." << "\n";
    delete this->pitch_view;
}
