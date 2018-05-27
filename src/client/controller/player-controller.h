#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "abstract-controller.h"
#include "../../shared/model/player.h"
#include "../view/player-view.h"
#include "../../shared/model/team.h"
#include "../view/camera.h"
#include <chrono>

class PlayerController : public AbstractController
{
    public:
        PlayerController(Team* team, Client* client);
        virtual ~PlayerController();
        void Handle(const Uint8* keyboard_state_array);

    protected:

    private:
        Team* team;
        //int current_action_timming;
        //PLAYER_ACTION current_action;
        Player* selected_player;
        std::chrono::time_point<std::chrono::system_clock> last_pass;
        static const unsigned int PASS_DELAY_MILLIS = 200;

        void PlayerPlay(const Uint8 *keyboard_state_array);
        void MovePlayer(const Uint8 *keyboard_state_array);
        void PassBall(const Uint8 *keyboard_state_array);
        bool PlayerRecoverBall(const Uint8 *keyboard_state_array);
        bool KickPlayer(const Uint8 *keyboard_state_array);
        bool UpKeySelected(const Uint8 *keyboard_state_array);
        bool RightKeySelected(const Uint8 *keyboard_state_array);
        bool LeftKeySelected(const Uint8 *keyboard_state_array);
        bool DownKeySelected(const Uint8 *keyboard_state_array);
        bool AKeySelected(const Uint8 *keyboard_state_array);
        bool SKeySelected(const Uint8 *keyboard_state_array);
        bool DKeySelected(const Uint8 *keyboard_state_array);
        bool ShiftKeySelected(const Uint8 *keyboard_state_array);
        bool ShouldRequestPass(const Uint8 *keyboard_state_array);
        bool SelectedPlayerHasChange();
        bool ContinueCurrentAction();
};

#endif // PLAYERCONTROLLER_H
