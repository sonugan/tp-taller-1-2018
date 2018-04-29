#ifndef TEAMCONTROLLER_H
#define TEAMCONTROLLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "abstract-controller.h"
#include "../../shared/model/player.h"
#include "../../shared/model/team.h"
#include "../../shared/model/formation.h"
#include "../view/camera.h"
#include "../game.h"
#include <vector>
#include <chrono>
#include "../sound/sound-manager.h"

class TeamController : public AbstractController
{
    public:
        TeamController(Team* team, Camera* camera);
        virtual ~TeamController();
        void Handle(const Uint8* keyboard_state_array);

    protected:

    private:
        static const unsigned int PLAYER_SELECTION_DELAY_MILLIS = 150;
        static const unsigned int FORMATION_CHANGE_DELAY_MILLIS = 150;
        bool CKeySelected(const Uint8 *keyboard_state_array);
        bool FKeySelected(const Uint8 *keyboard_state_array);
        void ChangePlayerSelection(const Uint8 *keyboard_state_array);
        bool PlayerWithinMargins(Player* player);
        Player* FindNextPlayerToSelect();
        void ChangeFormation(const Uint8 *keyboard_state_array);
        void MoveUnselectedPlayersToDefaultPositions();

        std::chrono::time_point<std::chrono::system_clock> last_player_selection_change;
        std::chrono::time_point<std::chrono::system_clock> last_formation_change;
        Team* team;
        Camera* camera;

};

#endif // TEAMCONTROLLER_H
