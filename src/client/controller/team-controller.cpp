#include "team-controller.h"

TeamController::TeamController(Team* team, Client* client, Camera* camera) { // @suppress("Class members should be properly initialized")
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

void TeamController::ChangePlayerSelection(const Uint8 *keyboard_state_array) {
    int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>
                             (std::chrono::system_clock::now()-last_player_selection_change).count();

    if (CKeySelected(keyboard_state_array) && elapsed_millis >= PLAYER_SELECTION_DELAY_MILLIS) {
        ChangePlayerRequest r;
        this->client->ChangePlayer(&r);
        this->sound_manager->PlayPlayerSelectionSound();
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


void TeamController::Handle(const Uint8* keyboard_state_array) {
    ChangeFormation(keyboard_state_array);
    ChangePlayerSelection(keyboard_state_array);
}
