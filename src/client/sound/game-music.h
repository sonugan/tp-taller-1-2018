#ifndef GAMEMUSIC_H
#define GAMEMUSIC_H

#include<iostream>
#include "SDL/SDL_mixer.h"
#include "../../shared/logger.h"

class GameMusic
{
    public:
        GameMusic();
        virtual ~GameMusic();

        void PlayMainTheme();
        void PlayLoginTheme();
        void Pause();
        void Resume();

    protected:

    private:
        const string MAIN_THEME_PATH = "src/client/sound/main_theme.wav";
        const string LOGIN_THEME_PATH = "src/client/sound/login_theme.wav";

        Mix_Music* current_track;

        bool LoadTrack(string track_path);
};

#endif // GAME-MUSIC_H
