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

Player* GameState::GetUserSelectedPlayer(std::vector<Player*> available_players)
{
    // TIENE QUE SER ALGUNO DE LOS DELANTEROS = POSICIONES 4, 5 O 6
    for (unsigned int i = 0; i < available_players.size(); i++) {
        Player* player = available_players[i];

        if (player->GetPositionIndex() >= 4 && player->GetPositionIndex() <= 6) {
            return player;
        }

    }

    return NULL;

}

void GameState::AddUser(User* user)
{
    pair<string, User*> user_entry = make_pair(user->GetUsername(), user);
//    this->active_users.insert(user_entry);

    // SETEO EL JUGADOR ACTIVO

    Team* selected_team = match->GetTeamB();

    if (user->GetSelectedTeam() == (int)TEAM_NUMBER::TEAM_A)
    {
        selected_team = match->GetTeamA();
    }

    Player* selected_player = this->GetUserSelectedPlayer(selected_team->GetAvailablePlayers());

    selected_player->SetPlayerColor(user->GetUserColor());
    user->SetSelectedPlayer(selected_player);

}

void GameState::RemoveUser(string username)
{
//    this->active_users.erase(username);
}


/* Private methods */
void GameState::CreateModel(Configuration* initial_configuration)
{
    Logger::getInstance()->debug("CREANDO EL MODELO");
    Pitch* pitch = new Pitch();

    Formation* formation_team_a = new Formation(initial_configuration->GetFormation(), TEAM_NUMBER::TEAM_A);
    Team* team_a = new Team(formation_team_a, initial_configuration->GetTeamName(), initial_configuration->GetShirt(), TEAM_NUMBER::TEAM_A);

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        team_a->AddPlayer(new Player(i,TEAM_NUMBER::TEAM_A));
    }

    Formation* formation_team_b = new Formation(initial_configuration->GetFormation(), TEAM_NUMBER::TEAM_B);
    Team* team_b = new Team(formation_team_b, "team_b", "away", TEAM_NUMBER::TEAM_B); // TODO: TRAER NOMBRE DEL TEAM B Y CAMISETA DE CONFIG

    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        team_b->AddPlayer(new Player(i, TEAM_NUMBER::TEAM_B));
    }

    Ball* ball = new Ball();

    this->match = new Match(pitch, team_a, team_b, ball);
}

Match* GameState::GetMatch()
{
    return this->match;
}

