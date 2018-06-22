#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SDL/SDL_mixer.h"
#include "../../shared/logger.h"

class SoundManager
{
    public:
        SoundManager();
        virtual ~SoundManager();
        void PlayPlayerSelectionSound();
        void PlayGameTimeStartSound();
        void PlayKickBallSound();
        void PlayGoalSound();
    protected:

    private:
        Mix_Chunk* sound;
        void PlaySound(char* path);
};

#endif // SOUNDMANAGER_H
