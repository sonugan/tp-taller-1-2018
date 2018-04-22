#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SDL/SDL_mixer.h"
#include "../common/logger.h"

class SoundManager
{
    public:
        SoundManager();
        virtual ~SoundManager();
        static void LoadResources();
        static void FreeResources();
        static void PlayPlayerSelectionSound();

    protected:

    private:
        static Mix_Chunk* change_player_sound;
};

#endif // SOUNDMANAGER_H
