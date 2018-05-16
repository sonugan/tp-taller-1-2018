#include "player-controller.h"

PlayerController::PlayerController(Team* team, Client* client) {
    this->team = team;
    this->client = client;
    current_action_timming = 1;
    current_action = PLAYER_IS_STILL;
    this->last_pass = std::chrono::system_clock::now();
}

PlayerController::~PlayerController() {
    //dtor
}

void PlayerController::PlayerPlay(const Uint8 *keyboard_state_array) {
    if(!ContinueCurrentAction())
    {
        selected_player = this->team->GetSelectedPlayer();
        bool playerKicked = this->KickPlayer(keyboard_state_array);

        if (!playerKicked) {
            bool playerRecovered = this->PlayerRecoverBall(keyboard_state_array);
            if (!playerRecovered) {
                this->MovePlayer(keyboard_state_array);
                this->PassBall(keyboard_state_array);
            }
        }
    }
}

void PlayerController::MovePlayer(const Uint8 *keyboard_state_array)
{
    bool run = ShiftKeySelected(keyboard_state_array);
    if (UpKeySelected(keyboard_state_array) && RightKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveUpToRight(run);
    } else if (UpKeySelected(keyboard_state_array) && LeftKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveUpToLeft(run);
    } else if (DownKeySelected(keyboard_state_array) && RightKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveDownToRight(run);
    } else if (DownKeySelected(keyboard_state_array) && LeftKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveDownToLeft(run);
    } else if (UpKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveUp(run);
    } else if(RightKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveRight(run);
    } else if(LeftKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveLeft(run);
    } else if(DownKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->MoveDown(run);
    }
    current_action = PLAYER_IS_RUNNING;
}

bool PlayerController::KickPlayer(const Uint8 *keyboard_state_array) {
    if (DKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->Kick();
        current_action = PLAYER_IS_KICKING;
        return true;
    }
    return false;
}

void PlayerController::PassBall(const Uint8 *keyboard_state_array) {
    unsigned int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_pass).count();
    if (elapsed_millis > PASS_DELAY_MILLIS && SKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->PassBall();
        last_pass = std::chrono::system_clock::now();
    }
}

bool PlayerController::PlayerRecoverBall(const Uint8 *keyboard_state_array) {
    if (AKeySelected(keyboard_state_array)) {
        team->GetSelectedPlayer()->RecoverBall();
        current_action = PLAYER_IS_RECOVERING;
        return true;
    }
    return false;
}

bool PlayerController::UpKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_UP];
}

bool PlayerController::RightKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_RIGHT];
}

bool PlayerController::LeftKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_LEFT];
}

bool PlayerController::DownKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_DOWN];
}

bool PlayerController::AKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_A];
}

bool PlayerController::SKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_S];
}

bool PlayerController::DKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_D];
}

bool PlayerController::ShiftKeySelected(const Uint8 *keyboard_state_array) {
    return keyboard_state_array[SDL_SCANCODE_LSHIFT];
}

void PlayerController::Handle(const Uint8* keyboard_state_array) {
    PlayerPlay(keyboard_state_array);
}

bool PlayerController::SelectedPlayerHasChange()
{
    return team->GetSelectedPlayer() != this->selected_player;
}

bool PlayerController::ContinueCurrentAction()
{
    if(!SelectedPlayerHasChange())
    {
        current_action_timming++;
        if(current_action == PLAYER_IS_KICKING &&
            (current_action_timming * PlayerView::FRAMES_PER_EVENT) < PlayerView::KICKING_FRAME_COUNT)
        {
            this->team->GetSelectedPlayer()->Kick();
            return true;
        }
        else if(current_action == PLAYER_IS_RECOVERING &&
            (current_action_timming * PlayerView::FRAMES_PER_EVENT) < PlayerView::RECOVERING_FRAME_COUNT)
        {
            this->team->GetSelectedPlayer()->RecoverBall();
            return true;
        }
        else
        {
            current_action_timming = 1;
            return false;
        }
    }
    else
    {
        current_action_timming = 1; //Es la segunda vez por la que debo entrar acá
        return false;
    }
}
