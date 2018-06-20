#ifndef GAMEMUSICCONTROLLER_H
#define GAMEMUSICCONTROLLER_H

#include <SDL2/SDL.h>
#include "../sound/game-music.h"
#include "abstract-controller.h"

class GameMusicController: public AbstractController
{
    public:
        GameMusicController(GameMusic* game_music);
        virtual ~GameMusicController();
        void Handle(const Uint8* keyboard_state_array);

    protected:

    private:
        bool paused;
        GameMusic* game_music;
        void PauseMusic(const Uint8 *keyboard_state_array);
        void ResumeMusic(const Uint8 *keyboard_state_array);

};

#endif // GAME-MUSIC-CONTROLLER_H
