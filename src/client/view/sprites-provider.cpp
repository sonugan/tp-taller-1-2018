#include "sprites-provider.h"
#include <sys/stat.h>

static bool File_Exists (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

SDL_Renderer* SpritesProvider::renderer = NULL;
std::map <unsigned int, SpriteSheet*> SpritesProvider::sprite_sheets;

SpritesProvider::SpritesProvider() {
    //ctor
}

SpritesProvider::~SpritesProvider() {

}

SpriteSheet* SpritesProvider::GetSheet(SPRITE_SHEET sprite_sheet_enum, std::string suggested_path) {
    if (sprite_sheets[sprite_sheet_enum] == NULL) {
        if (!suggested_path.empty() && File_Exists("src/client/sprites/" + suggested_path)) {
            sprite_sheets[sprite_sheet_enum] = new SpriteSheet(renderer, suggested_path);
        } else {
            if (!suggested_path.empty()) {
                //Logger::getInstance()->error("No se encontró la imagen '" + suggested_path + "'. Se procede a cargar la imagen por defecto.");
            }
            sprite_sheets[sprite_sheet_enum] = new SpriteSheet(renderer, GetDefaultPath(sprite_sheet_enum));
        }
    }
    return sprite_sheets[sprite_sheet_enum];
}

SpriteSheet* SpritesProvider::GetDefaultSheet(SPRITE_SHEET sprite_sheet_enum) {
    return GetSheet(sprite_sheet_enum, "");
}

std::string SpritesProvider::GetDefaultPath(SPRITE_SHEET sprite_sheet_enum) {
    if (SELECTOR_A1 == sprite_sheet_enum) {
        return "selectors/selector1.png";
    } else if (SELECTOR_A2 == sprite_sheet_enum) {
        return "selectors/selector1.png";
    } else if (SELECTOR_A3 == sprite_sheet_enum) {
        return "selectors/selector1.png";
    } else if (SELECTOR_A4 == sprite_sheet_enum) {
        return "selectors/selector1.png";
    } else if (TEAM_A_PLAYER == sprite_sheet_enum) {
        return "team_a/home-kit.png";
    } else if (TEAM_B_PLAYER == sprite_sheet_enum) {
        return "team_b/home-kit.png";
    } else if (PITCH == sprite_sheet_enum) {
        return "pitch.jpg";
    } else if (BALL == sprite_sheet_enum) {
        return "ball.png";
    }
    return NULL;
}

void SpritesProvider::FreeResources() {
    for ( const auto &key_value_pair : sprite_sheets ) {
        delete SpritesProvider::sprite_sheets[key_value_pair.first];
    }
    SpritesProvider::sprite_sheets.clear();
}

void SpritesProvider::SetRenderer(SDL_Renderer* renderer) {
    SpritesProvider::renderer = renderer;
}