#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../common/abstract-controller.h"
#include "../player/player.h"
#include "../team/team.h"
#include "../camera/camera.h"

class PlayerController : public AbstractController
{
    public:
        PlayerController(Team* team, Camera* camera);
        virtual ~PlayerController();
        void Handle(const Uint8* keyboard_state_array);

    protected:

    private:
        Team* team;
        Camera* camera;

        void PlayerPlay(const Uint8 *keyboard_state_array);
        void MovePlayer(const Uint8 *keyboard_state_array);
        bool PlayerRecoverBall(const Uint8 *keyboard_state_array);
        bool KickPlayer(const Uint8 *keyboard_state_array);
        bool UpKeySelected(const Uint8 *keyboard_state_array);
        bool RightKeySelected(const Uint8 *keyboard_state_array);
        bool LeftKeySelected(const Uint8 *keyboard_state_array);
        bool DownKeySelected(const Uint8 *keyboard_state_array);
        bool SpaceBarSelected(const Uint8 *keyboard_state_array);
};

#endif // PLAYERCONTROLLER_H
