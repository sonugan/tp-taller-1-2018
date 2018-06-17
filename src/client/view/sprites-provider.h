#ifndef SPRITESPROVIDER_H
#define SPRITESPROVIDER_H

#include "sprite-sheet.h"
#include "../../shared/logger.h"
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum SPRITE_SHEET {TEAM_A_PLAYER, TEAM_B_PLAYER, SELECTOR_A1, SELECTOR_A2, SELECTOR_A3, SELECTOR_A4, PITCH, BALL, INFO_PANEL_BACK, TEAM_A_MINI_PLAYER, TEAM_B_MINI_PLAYER, MINI_BALL, KEEPER};
class SpritesProvider
{
    public:
        virtual ~SpritesProvider();
        static SpriteSheet* GetSheet(SPRITE_SHEET sprite_sheet_enum, std::string suggested_path);
        static SpriteSheet* GetDefaultSheet(SPRITE_SHEET sprite_sheet_enum);
        static void SetRenderer(SDL_Renderer* renderer);
        static void FreeResources();

    protected:

    private:
        SpritesProvider();
        static std::map <unsigned int, SpriteSheet*> sprite_sheets;
        static SDL_Renderer* renderer;
        static std::string GetDefaultPath(SPRITE_SHEET sprite_sheet_enum);
};

#endif // SPRITESPROVIDER_H
