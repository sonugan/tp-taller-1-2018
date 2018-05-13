#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include "view/sprite-sheet.h"
#include "view/sprites-provider.h"
#include "../shared/model/pitch.h"
#include "view/pitch-view.h"
#include "view/ball-view.h"
#include "view/player-view.h"
#include "view/camera.h"
#include "../shared/model/match.h"
#include "../shared/model/player.h"
#include "controller/player-controller.h"
#include "../shared/model/team.h"
#include "controller/team-controller.h"
#include "../shared/model/formation.h"
#include "../shared/configuration/configuration.h"
#include "controller/game-controller.h"
#include "client.h"
#include <map>

class GameController; //  forward declaration
class PlayerController; //  forward declaration
class TeamController; //  forward declaration
class Game
{
    public:
        Game(Configuration* initial_configuration);
        virtual ~Game();
        void Start();
        void End();
        void RequestQuit();
        bool IsCorrectlyInitialized();
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
        PlayerController* player_controller;
        GameController* game_controller;
        bool quit;
        bool correctly_initialized;

        void CreateModel();
        void CreateViews();
        void CreateControllers();
        void DestroyModel();
        void DestroyViews();
        void DestroyControllers();
        void InitSDL();
        void CloseSDL();
        void RenderViews();

};

#endif // GAME_H
