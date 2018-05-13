#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sprite-sheet.h"
#include "sprite-text.h"
#include "../shared/logger.h"
#include "../shared/network/login.cpp"
#include "../shared/configuration/configuration.h"
#include <string>

using namespace std;

class LoginView
{
    public:
        LoginView(SDL_Renderer* renderer, int height, int width, Login* login);
        void Free();
        void Open(Configuration* game_configuration);
        void OpenErrorPage(Configuration* game_configuration);
        bool IsUserAuthenticated();
        bool IsUserQuit();
        TEAM_NUMBER GetTeamNumber();
        ~LoginView();

    protected:
        string BACKGROUND_IMAGE = "tehkan_world_cup_menu.jpg";
        string DISPLAY_FONT = "src/client/sprites/tehkan_world_cup.ttf";
        TEAM_NUMBER team_number;
        bool userAuthenticated;
        bool userQuit;
        TTF_Font* fontStyle = NULL;
        SDL_Renderer* renderer;
        SpriteText* textSprite;
        SpriteText* inputTextSprite;
        SpriteSheet* backgroundSprite;
        int screenHeight;
        int screenWidth;
    private:
        Login* login;
};

#endif // LOGINVIEW_H
