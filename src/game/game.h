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
#include "../player/player-controller.h"
#include "../team/team.h"
#include "../team/team-controller.h"
#include "../team/formation.h"
#include "../configuration/configuration.h"
#include "game-controller.h"
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
