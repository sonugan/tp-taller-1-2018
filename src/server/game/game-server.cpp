#include "game-server.h"

#include "../../shared/logger.h"


GameServer::GameServer(Configuration* initial_configuration)
{
    this->game_state = new GameState(initial_configuration);
}

GameServer::~GameServer()
{
    delete this->game_state;
}

void GameServer::Start()
{
    Logger::getInstance()->info("(GameServer:Start) Comenzando juego.");
    this->is_running = true;
    while(this->is_running)
    {
        //gameloop
    }
}

void GameServer::Stop()
{
    Logger::getInstance()->info("(GameServer:Start) Deteniendo juego.");
    this->is_running = false;
}



