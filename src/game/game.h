#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include "../common/sprite-sheet.h"
#include "../pitch/pitch.h"
#include "../pitch/pitch-view.h"
#include "../player/player-view.h"
#include "../camera/camera.h"
#include "../match/match.h"
#include "../player/player.h"
#include "../team/team.h"
#include "../team/team-controller.h"
#include "../team/formation.h"
#include "../configuration/configuration.h"
#include <map>

class TeamController; //  forward declaration
class Game
{
    public:
        Game(Configuration* initial_configuration);
        virtual ~Game();
        void Start();
        void End();
        static const int SCREEN_WIDTH = 800;
        static const int SCREEN_HEIGHT = 600;
        static const unsigned int PITCH_WIDTH = 1920;
        static const unsigned int PITCH_HEIGHT = 1080;
    protected:

    private:

        Configuration* initial_configuration;
        SDL_Window* window;
        SDL_Renderer* renderer;
        Match* match;
        Camera* camera;
        static const int FRAMES_PER_SECOND = 30;
        TeamController* team_controller;
        bool quit;

        void CreateModel();
        void CreateViews();
        void CreateControllers();
        void DestroyModel();
        void DestroyViews();
        void InitSDL();
        void CloseSDL();
        void RenderViews();
        void PlayerPlay(const Uint8 *keyboard_state_array);
        void MovePlayer(const Uint8 *keyboard_state_array);
        void MoveUnselectedPlayersToDefaultPositions();
        bool PlayerRecoverBall(const Uint8 *keyboard_state_array);
        bool KickPlayer(const Uint8 *keyboard_state_array);
        Uint8 GetSelectedKey(const Uint8* keyboard_state_array);
        bool UpKeySelected(const Uint8 *keyboard_state_array);
        bool RightKeySelected(const Uint8 *keyboard_state_array);
        bool LeftKeySelected(const Uint8 *keyboard_state_array);
        bool DownKeySelected(const Uint8 *keyboard_state_array);
        bool SpaceBarSelected(const Uint8 *keyboard_state_array);
        void ExitGame(const Uint8 *keyboard_state_array);



};

#endif // GAME_H
