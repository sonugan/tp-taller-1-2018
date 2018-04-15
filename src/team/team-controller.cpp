#include "team-controller.h"

TeamController::TeamController(Team* team, Camera* camera) {
    this->team = team;
    this->camera = camera;
    this->last_player_selection_change = std::chrono::system_clock::now();
    this->last_formation_change = std::chrono::system_clock::now();
}

TeamController::~TeamController() {
    //dtor
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
    return x >= (Camera::CAMERA_MARGIN - half_player_sprite_size) && y >= (Camera::CAMERA_MARGIN - half_player_sprite_size) && x <= (Game::SCREEN_WIDTH - Camera::CAMERA_MARGIN + half_player_sprite_size) && y <= (Game::SCREEN_HEIGHT - Camera::CAMERA_MARGIN + half_player_sprite_size);
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
            // El próximo jugador tiene que estar dentro de la cámara y no tiene que estar seleccionado
            Player* possible_player = team->GetPlayers()[new_selected_player_position_index];
            if (!possible_player->IsSelected() && PlayerWithinMargins(possible_player)) {
                next_player = possible_player;
                break;
            }
    }
    return next_player;
}

void TeamController::ChangePlayerSelection(const Uint8 *keyboard_state_array) {

    int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>
                             (std::chrono::system_clock::now()-last_player_selection_change).count();

    if (elapsed_millis >= PLAYER_SELECTION_DELAY_MILLIS) {
        if(CKeySelected(keyboard_state_array)) {
            Player* next_player = FindNextPlayerToSelect();
            if (next_player != NULL) {
                Player* selected_player = team->GetSelectedPlayer();
                selected_player->SetSelected(false);
                selected_player = next_player;
                selected_player->SetSelected(true);
                camera->UpdateLocatable(selected_player->GetPositionIndex());
                last_player_selection_change = std::chrono::system_clock::now();
            }
        }
    }

}

void TeamController::ChangeFormation(const Uint8 *keyboard_state_array) {

    int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>
                             (std::chrono::system_clock::now()-last_formation_change).count();

    if (elapsed_millis >= FORMATION_CHANGE_DELAY_MILLIS) {
        if(FKeySelected(keyboard_state_array)) {
            FORMATION old_formation_value = team->GetFormation()->GetValue();
            if (old_formation_value == F_3_3) {
                team->SetFormation(new Formation(F_3_2_1));
            } else if (old_formation_value == F_3_2_1) {
                team->SetFormation(new Formation(F_3_1_2));
            } else if (old_formation_value == F_3_1_2) {
                team->SetFormation(new Formation(F_3_3));
            }
            last_formation_change = std::chrono::system_clock::now();
        }
    }
}

void TeamController::Handle(const Uint8* keyboard_state_array) {
    ChangeFormation(keyboard_state_array);
    ChangePlayerSelection(keyboard_state_array);
}


