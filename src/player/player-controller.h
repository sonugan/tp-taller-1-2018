#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../common/abstract-controller.h"
#include "../player/player.h"
#include "../player/player-view.h"
#include "../team/team.h"
#include "../camera/camera.h"

class PlayerController : public AbstractController
{
    public:
        PlayerController(Team* team);
        virtual ~PlayerController();
        void Handle(const Uint8* keyboard_state_array);

    protected:

    private:
        Team* team;

        void PlayerPlay(const Uint8 *keyboard_state_array);
        void MovePlayer(const Uint8 *keyboard_state_array);
        bool PlayerRecoverBall(const Uint8 *keyboard_state_array);
        bool KickPlayer(const Uint8 *keyboard_state_array);
        bool UpKeySelected(const Uint8 *keyboard_state_array);
        bool RightKeySelected(const Uint8 *keyboard_state_array);
        bool LeftKeySelected(const Uint8 *keyboard_state_array);
        bool DownKeySelected(const Uint8 *keyboard_state_array);
        bool SpaceBarSelected(const Uint8 *keyboard_state_array);
        int current_action_timming;
        PLAYER_ACTION current_action;
};

#endif // PLAYERCONTROLLER_H
