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
        void PlayKickOffSound();
        void PlayKickBallSound();
        void PlayGoalSound();
        void PlayTimeUpSound();
        void DeleteSound();
    protected:

    private:
        Mix_Chunk* sound;
        void PlaySound(char* path);
        bool IsPlayingSound();
};

#endif // SOUNDMANAGER_H
