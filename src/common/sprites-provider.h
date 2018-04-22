#ifndef SPRITESPROVIDER_H
#define SPRITESPROVIDER_H

#include "sprite-sheet.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SpritesProvider
{
    public:
        virtual ~SpritesProvider();
        static SpriteSheet* GetSelectorSheet(SDL_Renderer* renderer, std::string file_path);
        static SpriteSheet* GetPlayerSheet(SDL_Renderer* renderer, std::string file_path);
        static void FreeResources();

    protected:

    private:
        SpritesProvider();
        static SpriteSheet* player_sheet;
        static SpriteSheet* selector_sheet;
};

#endif // SPRITESPROVIDER_H
