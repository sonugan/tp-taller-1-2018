#include "game-music.h"

GameMusic::GameMusic()
{
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
    {
        Logger::getInstance()->debug("Error al cargar musica del juego:");
        Logger::getInstance()->debug(Mix_GetError());
    }

    this->current_track = NULL;
}

GameMusic::~GameMusic()
{
    if (this->current_track != NULL)
    {
        Mix_FreeMusic(this->current_track);
        this->current_track = NULL;
    }
    Mix_CloseAudio();
}

bool GameMusic::LoadTrack(string track_path)
{
    if (this->current_track != NULL)
    {
        Mix_FreeMusic(this->current_track);
        this->current_track = NULL;
    }

    this->current_track = Mix_LoadMUS(track_path.c_str());

    if (this->current_track == NULL)
    {
        Logger::getInstance()->debug("Error al cargar musica del juego: ");
        Logger::getInstance()->debug(Mix_GetError());
        return false;
    }

    return true;
}

void GameMusic::PlayMainTheme()
{
    bool loaded_track = this->LoadTrack(MAIN_THEME_PATH);

    if (loaded_track)
    {
        Mix_PlayMusic(this->current_track, -1);
    }
}

void GameMusic::PlayLoginTheme()
{
    bool loaded_track = this->LoadTrack(LOGIN_THEME_PATH);

    if (loaded_track)
    {
        Mix_PlayMusic(this->current_track, -1);
    }
}

void GameMusic::Pause()
{
    Mix_PauseMusic();
}

void GameMusic::Resume()
{
    Mix_ResumeMusic();
}

