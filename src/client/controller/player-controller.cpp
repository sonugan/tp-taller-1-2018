#include "player-controller.h"

//Agregar los request que son los que se van a mandar al servidor.

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
    Logger::getInstance()->debug("(PlayerController::PlayerPlay)");
    if(!ContinueCurrentAction())
    {
        selected_player = this->team->GetSelectedPlayer();
        bool playerKicked = this->KickPlayer(keyboard_state_array);

        if (!playerKicked) {
            bool playerRecovered = this->PlayerRecoverBall(keyboard_state_array);
            if (!playerRecovered) {
                this->PassBall(keyboard_state_array);
                this->MovePlayer(keyboard_state_array);
            }
        }
    }
}

void PlayerController::MovePlayer(const Uint8 *keyboard_state_array)
{
    Logger::getInstance()->debug("(PlayerController::MovePlayer)");
    bool run = ShiftKeySelected(keyboard_state_array);

    if (UpKeySelected(keyboard_state_array) && RightKeySelected(keyboard_state_array)) {
        MoveRequest m(DIRECTION::NORTHEAST, run);
        this->client->Move(&m);
    } else if (UpKeySelected(keyboard_state_array) && LeftKeySelected(keyboard_state_array)) {
        MoveRequest m(DIRECTION::NORTHWEST, run);
        this->client->Move(&m);
    } else if (DownKeySelected(keyboard_state_array) && RightKeySelected(keyboard_state_array)) {
        MoveRequest m(DIRECTION::SOUTHEAST, run);
        this->client->Move(&m);
    } else if (DownKeySelected(keyboard_state_array) && LeftKeySelected(keyboard_state_array)) {
        MoveRequest m(DIRECTION::SOUTHWEST, run);
        this->client->Move(&m);
    } else if (UpKeySelected(keyboard_state_array)) {
        MoveRequest m(DIRECTION::NORTH, run);
        this->client->Move(&m);
    } else if(RightKeySelected(keyboard_state_array)) {
        MoveRequest m(DIRECTION::EAST, run);
        this->client->Move(&m);
    } else if(LeftKeySelected(keyboard_state_array)) {
        MoveRequest m(DIRECTION::WEST, run);
        this->client->Move(&m);
    } else if(DownKeySelected(keyboard_state_array)) {
        MoveRequest m(DIRECTION::SOUTH, run);
        this->client->Move(&m);
    }
    current_action = PLAYER_IS_RUNNING;
}

bool PlayerController::KickPlayer(const Uint8 *keyboard_state_array) {
    if (DKeySelected(keyboard_state_array)) {
        KickBallRequest r;
        this->client->KickBall(&r);
        current_action = PLAYER_IS_KICKING;
        return true;
    }
    return false;
}

void PlayerController::PassBall(const Uint8 *keyboard_state_array) {
    if (ShouldRequestPass(keyboard_state_array)) {
        PassBallRequest r;
        this->client->PassBall(&r);
        last_pass = std::chrono::system_clock::now();
    }
}

bool PlayerController::ShouldRequestPass(const Uint8 *keyboard_state_array) {
    unsigned int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_pass).count();
    return (elapsed_millis > PASS_DELAY_MILLIS) && SKeySelected(keyboard_state_array) && SKeySelected(keyboard_state_array);
}

bool PlayerController::PlayerRecoverBall(const Uint8 *keyboard_state_array) {
    Logger::getInstance()->debug("(PlayerController::PlayerRecoverBall)");
    if (AKeySelected(keyboard_state_array)) {
        RecoverBallRequest r;
        this->client->RecoverBall(&r);
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
    Logger::getInstance()->debug("(PlayerController::SelectedPlayerHasChange)");
    return team->GetSelectedPlayer() != this->selected_player;

}

bool PlayerController::ContinueCurrentAction()
{
    Logger::getInstance()->debug("(PlayerController::ContinueCurrentAction)");
    if(!SelectedPlayerHasChange())
    {
        current_action_timming++;
        if(current_action == PLAYER_IS_KICKING &&
            (current_action_timming * PlayerView::FRAMES_PER_EVENT) < PlayerView::KICKING_FRAME_COUNT)
        {
            KickBallRequest r;
            this->client->KickBall(&r);
            return true;
        }
        else if(current_action == PLAYER_IS_RECOVERING &&
            (current_action_timming * PlayerView::FRAMES_PER_EVENT) < PlayerView::RECOVERING_FRAME_COUNT)
        {
            RecoverBallRequest r;
            this->client->RecoverBall(&r);
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
