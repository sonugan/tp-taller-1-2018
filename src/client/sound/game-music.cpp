#include "game-music.h"

GameMusic::GameMusic()
{
    Logger::getInstance()->debug("(GameMusic::Creando musica del juego)");

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
    {
        Logger::getInstance()->debug("Error al cargar musica del juego:");
        Logger::getInstance()->debug(Mix_GetError());
    }

    this->current_track = NULL;
}

GameMusic::~GameMusic()
{
    Logger::getInstance()->debug("DESTRUYENDO GAME MUSIC");
    if (this->current_track != NULL)
    {
        Mix_FreeMusic(this->current_track);
        this->current_track = NULL;
    }
    Mix_CloseAudio();
}

bool GameMusic::LoadTrack(string track_path)
{
    Logger::getInstance()->debug("(GameMusic::Cargando track seleccionado)");

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

    Logger::getInstance()->debug("(GameMusic::Track cargado correctamente)");

    return true;
}

void GameMusic::PlayMainTheme()
{
    Logger::getInstance()->debug("(GameMusic::Track seleccionado es MAIN THEME)");

    bool loaded_track = this->LoadTrack(MAIN_THEME_PATH);

    if (loaded_track)
    {
        Logger::getInstance()->debug("(GameMusic::MAIN THEME sonando)");
        Mix_PlayMusic(this->current_track, FOREVER);
    }
}

void GameMusic::PlayLoginTheme()
{
    Logger::getInstance()->debug("(GameMusic::Track seleccionado es LOGIN THEME)");

    bool loaded_track = this->LoadTrack(LOGIN_THEME_PATH);

    if (loaded_track)
    {
        Logger::getInstance()->debug("(GameMusic::LOGIN THEME sonando)");
        Mix_PlayMusic(this->current_track, FOREVER);
    }
}

void GameMusic::Pause()
{
    Logger::getInstance()->debug("(GameMusic::Musica pausada)");
    Mix_PauseMusic();
}

void GameMusic::Resume()
{
    Logger::getInstance()->debug("(GameMusic::Reanudando musica)");
    Mix_ResumeMusic();
}

