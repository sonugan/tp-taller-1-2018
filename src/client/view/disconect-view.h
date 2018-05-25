#ifndef DISCONECTVIEW_H
#define DISCONECTVIEW_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sprite-sheet.h"
#include "sprite-text.h"
#include "../../shared/logger.h"
#include <string>

using namespace std;

class DisconetView
{
    public:
        DisconetView(SDL_Renderer* renderer, int height, int width);
        void Free();
        void OpenConectionErrorPage();
        void OpenConectingPage();
        ~DisconetView();
        bool ExitGame();
        bool Reconnect();

    protected:
        string BACKGROUND_IMAGE = "tehkan_world_cup_menu.jpg";
        string DISPLAY_FONT = "src/client/sprites/tehkan_world_cup.ttf";
        TTF_Font* fontStyle = NULL;
        SDL_Renderer* renderer;
        SpriteText* textSprite;
        SpriteSheet* backgroundSprite;
        int screenHeight;
        int screenWidth;
    private:
        bool reconnect;
        bool exit_game;
};

#endif // DISCONECTVIEW_H
