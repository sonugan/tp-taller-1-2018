#include "game-state.h"

#include "../../shared/logger.h"
#include "../../shared/model/pitch.h"
#include "../../shared/model/formation.h"
#include "../../shared/model/team.h"
#include "../../shared/model/player.h"
#include "../../shared/model/ball.h"

GameState::GameState(Configuration* initial_configuration)
{
    this->CreateModel(initial_configuration);
}

GameState::~GameState()
{
    delete this->match;
}


/* Private methods */
void GameState::CreateModel(Configuration* initial_configuration)
{
    Logger::getInstance()->debug("(GameState:CreateModel) Instanciando el modelo.");

    Pitch* pitch = new Pitch();

    Formation* formation = new Formation(initial_configuration->GetFormation());
    Team* team_a = new Team(formation, initial_configuration->GetTeamName(), initial_configuration->GetShirt());

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++)
    {
        team_a->AddPlayer(new Player(i));
    }

    //selecciono por default al arquero
    team_a->GetPlayers()[0]->SetSelected(true);

    Ball* ball = new Ball();

    this->match = new Match(pitch, team_a, NULL, ball);
}
