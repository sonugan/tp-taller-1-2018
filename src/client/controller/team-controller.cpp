#include "team-controller.h"

TeamController::TeamController(Team* team, Client* client, Camera* camera) {
    this->team = team;
    this->client = client;
    this->camera = camera;
    this->last_player_selection_change = std::chrono::system_clock::now();
    this->last_formation_change = std::chrono::system_clock::now();
}

TeamController::~TeamController() {
    //dtor
}

void TeamController::SetColor(USER_COLOR color){
    this->color = color;
}

bool TeamController::CKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_C];
}

bool TeamController::FKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_F];
}

bool TeamController::PlayerWithinMargins(Player* player) {
    //  64 es el tamaño del sprite del player... magic number.
    int half_player_sprite_size = 32;
    int x = player->GetLocation()->GetX() - camera->area->x;
    int y = player->GetLocation()->GetY() - camera->area->y;
    return x >= (Camera::CAMERA_MARGIN - half_player_sprite_size) && y >= (Camera::CAMERA_MARGIN - half_player_sprite_size) && x <= (Game::SCREEN_WIDTH - Camera::CAMERA_MARGIN - half_player_sprite_size) && y <= (Game::SCREEN_HEIGHT - Camera::CAMERA_MARGIN - half_player_sprite_size);
}

Player* TeamController::FindNextPlayerToSelect() {
    Player* next_player = NULL;
    unsigned int new_selected_player_position_index = team->GetSelectedPlayer()->GetPositionIndex();
    for (unsigned int i = 0; i < (Team::TEAM_SIZE - 1); i++) {

            if (new_selected_player_position_index == Team::TEAM_SIZE-1) {
                new_selected_player_position_index = 0;
            } else {
                new_selected_player_position_index++;
            }

            Player* possible_player = team->GetPlayers()[new_selected_player_position_index];
            if (!possible_player->IsSelected()) {
                next_player = possible_player;
                break;
            }
    }
    return next_player;
}

/*
void TeamController::ChangePlayerSelection(const Uint8 *keyboard_state_array) {

    int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>
                             (std::chrono::system_clock::now()-last_player_selection_change).count();

    if (CKeySelected(keyboard_state_array) && !team->GetSelectedPlayer()->HasBall() && elapsed_millis >= PLAYER_SELECTION_DELAY_MILLIS) {
        Player* next_player = FindNextPlayerToSelect();
        if (next_player != NULL) {
            SoundManager::PlayPlayerSelectionSound();
            Player* selected_player = team->GetSelectedPlayer();
            USER_COLOR color = selected_player->GetPlayerColor();
            selected_player->SetPlayerColor(USER_COLOR::NO_COLOR);
            selected_player = next_player;
            selected_player->SetPlayerColor(color);
            last_player_selection_change = std::chrono::system_clock::now();
        }
    }

}*/

void TeamController::ChangePlayerSelection(const Uint8 *keyboard_state_array) {
    int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>
                             (std::chrono::system_clock::now()-last_player_selection_change).count();

    std::vector<Player*> players = team->GetPlayers();
    Player* player = NULL;
    for (unsigned int i = 0; i < (Team::TEAM_SIZE - 1); i++) {
        if (players[i]->GetPlayerColor() == this->color){
            player = players[i];
        }
    }
    if (CKeySelected(keyboard_state_array) && !player->HasBall() && elapsed_millis >= PLAYER_SELECTION_DELAY_MILLIS) {
        ChangePlayerRequest r;
        this->client->ChangePlayer(&r);
        last_player_selection_change = std::chrono::system_clock::now();
    }
}

void TeamController::ChangeFormation(const Uint8 *keyboard_state_array) {

    int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>
                             (std::chrono::system_clock::now()-last_formation_change).count();

    if (elapsed_millis >= FORMATION_CHANGE_DELAY_MILLIS) {
        if(FKeySelected(keyboard_state_array)) {
            FORMATION old_formation_value = team->GetFormation()->GetValue();
            if (old_formation_value == F_3_3) {
                team->SetFormation(new Formation(F_3_2_1, this->team->GetTeamNumber()));
            } else if (old_formation_value == F_3_2_1) {
                team->SetFormation(new Formation(F_3_1_2, this->team->GetTeamNumber()));
            } else if (old_formation_value == F_3_1_2) {
                team->SetFormation(new Formation(F_3_3, this->team->GetTeamNumber()));
            }
            last_formation_change = std::chrono::system_clock::now();
        }
    }
}

void TeamController::MoveUnselectedPlayersToDefaultPositions() {
    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        Player* player = team->GetPlayers()[i];
        if (!player->IsSelected()) {
            player->GoBackToDefaultPosition();
        }
    }
}

void TeamController::CatchBall() {

    if (team->GetMatch()->GetBall()->LastFreedDelayPassed()) {
        for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
            Player* player = team->GetPlayers()[i];
            player->CatchBall();
            if (player->HasBall()) {

            }
        }
    }
}

void TeamController::Handle(const Uint8* keyboard_state_array) {
    ChangeFormation(keyboard_state_array);
    ChangePlayerSelection(keyboard_state_array);
    MoveUnselectedPlayersToDefaultPositions();
    CatchBall();
}


