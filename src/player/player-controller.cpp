#include "player-controller.h"

PlayerController::PlayerController(Team* team) {
    this->team = team;
    current_action_timming = 0;
    current_action = PLAYER_IS_STILL;
}

PlayerController::~PlayerController() {
    //dtor
}

void PlayerController::PlayerPlay(const Uint8 *keyboard_state_array) {
    if(current_action == PLAYER_IS_KICKING && (current_action_timming * PlayerView::FRAMES_PER_EVENT) < PlayerView::KICKING_FRAME_COUNT)
    {
        team->GetSelectedPlayer()->Kick();
        current_action_timming++;
    }
    else if(current_action == PLAYER_IS_RECOVERING && (current_action_timming * PlayerView::FRAMES_PER_EVENT) < PlayerView::RECOVERING_FRAME_COUNT)
    {
        team->GetSelectedPlayer()->RecoverBall();
        current_action_timming++;
    }
    else
    {
        current_action_timming = 0;
        bool playerKicked = this->KickPlayer(keyboard_state_array);

        if (!playerKicked) {
            bool playerRecovered = this->PlayerRecoverBall(keyboard_state_array);
            if (!playerRecovered) {
                this->MovePlayer(keyboard_state_array);
            }
        }
    }
}

void PlayerController::MovePlayer(const Uint8 *keyboard_state_array)
{
    if (UpKeySelected(keyboard_state_array) && RightKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveUpToRight();
    } else if (UpKeySelected(keyboard_state_array) && LeftKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveUpToLeft();
    } else if (DownKeySelected(keyboard_state_array) && RightKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveDownToRight();
    } else if (DownKeySelected(keyboard_state_array) && LeftKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveDownToLeft();
    } else if (UpKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveUp();
    } else if(RightKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveRight();
    } else if(LeftKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveLeft();
    } else if(DownKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveDown();
    }
    current_action = PLAYER_IS_RUNNING;
}

bool PlayerController::KickPlayer(const Uint8 *keyboard_state_array) {
    if (SpaceBarSelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->Kick();
        current_action = PLAYER_IS_KICKING;
        return true;
    }
    return false;
}

bool PlayerController::PlayerRecoverBall(const Uint8 *keyboard_state_array) {
    if (keyboard_state_array[SDL_SCANCODE_V]) {
        team->GetSelectedPlayer()->RecoverBall();
        current_action = PLAYER_IS_RECOVERING;
        return true;
    }
    return false;
}

bool PlayerController::UpKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_UP] || keyboard_state_array[SDL_SCANCODE_W];
}

bool PlayerController::RightKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_RIGHT] || keyboard_state_array[SDL_SCANCODE_D];
}

bool PlayerController::LeftKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_LEFT] || keyboard_state_array[SDL_SCANCODE_A];
}

bool PlayerController::DownKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_DOWN] || keyboard_state_array[SDL_SCANCODE_S];
}

bool PlayerController::SpaceBarSelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_SPACE];
}

void PlayerController::Handle(const Uint8* keyboard_state_array) {
    PlayerPlay(keyboard_state_array);
}
