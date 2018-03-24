#include "game.h"
#include <iostream>

Game::Game()
{
    //ctor
    this->pitch = new Pitch();
    this->player = new Player();
}

Game::~Game()
{
    std::cout << "destructor de game";
    //dtor
    delete this->pitch;
    delete this->player;
}

void Game::Start()
{
    std::cout << "start game...";
}
