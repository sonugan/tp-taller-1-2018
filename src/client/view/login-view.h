#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sprite-sheet.h"
#include <string>

using namespace std;

class LoginView
{
    public:
        LoginView(SDL_Renderer* renderer, int height, int width);
        void Free();
        void Open();
        bool IsUserAuthenticated();
    protected:
        ~LoginView();
        string BACKGROUND_IMAGE = "tehkan_world_cup_menu.jpg";
        string DISPLAY_FONT = "src/client/sprites/tehkan_world_cup.ttf";
        string userName;
        string userPassword;
        bool userAuthenticated;
        TTF_Font* fontStyle = NULL;
        SDL_Renderer* renderer;
        SpriteSheet* textSprite;
        SpriteSheet* inputTextSprite;
        SpriteSheet* backgroundSprite;
        int screenHeight;
        int screenWidth;
};

#endif // LOGINVIEW_H
