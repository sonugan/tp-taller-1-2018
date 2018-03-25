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
#include "../player/player.h"
#include "../player/player-view.h"
#include "../camera/camera.h"

class Game
{
    public:
        Game();
        virtual ~Game();
        void Start();
        void End();
        static const int SCREEN_WIDTH = 800;
        static const int SCREEN_HEIGHT = 600;
        static const unsigned int PITCH_WIDTH = 1920;
        static const unsigned int PITCH_HEIGHT = 1080;
    protected:

    private:

        SDL_Window* window;
        SDL_Renderer* renderer;
        Pitch* pitch;
        Player* player;
        Camera* camera;
        std::vector<AbstractView*> views;

        void CreateModel();
        void CreateViews();
        void DestroyModel();
        void DestroyViews();
        void InitSDL();
        void CloseSDL();
        void RenderViews();
};

#endif // GAME_H
