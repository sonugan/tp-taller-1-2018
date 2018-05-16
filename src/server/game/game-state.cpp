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

void GameState::AddUser(User* user)
{
    pair<string, User*> user_entry = make_pair(user->GetUsername(), user);
    this->active_users.insert(user_entry);
}

void GameState::RemoveUser(string username)
{
    this->active_users.erase(username);
}


/* Private methods */
void GameState::CreateModel(Configuration* initial_configuration)
{
/*    Logger::getInstance()->debug("(GameState:CreateModel) Instanciando el modelo.");

    Pitch* pitch = new Pitch();

    Formation* formation = new Formation(initial_configuration->GetFormation(), TEAM_A);
    Team* team_a = new Team(formation, initial_configuration->GetTeamName(), initial_configuration->GetShirt());

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++)
    {
        team_a->AddPlayer(new Player(i));
    }

    //selecciono por default al arquero
    team_a->GetPlayers()[0]->SetSelected(true);

    Ball* ball = new Ball();

    this->match = new Match(pitch, team_a, NULL, ball);
*/
}
