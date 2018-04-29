#include "sprites-provider.h"

SpriteSheet* SpritesProvider::player_sheet = NULL;
SpriteSheet* SpritesProvider::selector_sheet = NULL;

SpritesProvider::SpritesProvider()
{
    //ctor
}

SpritesProvider::~SpritesProvider()
{

}


SpriteSheet* SpritesProvider::GetPlayerSheet(SDL_Renderer* renderer, std::string file_path) {
    if (player_sheet == NULL) {
        player_sheet = new SpriteSheet(renderer, file_path);
    }
    return player_sheet;
}

SpriteSheet* SpritesProvider::GetSelectorSheet(SDL_Renderer* renderer, std::string file_path) {
    if (selector_sheet == NULL) {
        selector_sheet = new SpriteSheet(renderer, file_path);
    }
    return selector_sheet;
}

void SpritesProvider::FreeResources() {
    if (player_sheet != NULL) {
        delete player_sheet;
    }
    if (selector_sheet != NULL) {
        delete selector_sheet;
    }
}
