#include "sound-manager.h"

SoundManager::SoundManager()
{
    this->sound = NULL;
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024) == -1)
    {
        Logger::getInstance()->debug("(SoundManager::Error al abrir canal para sonido)");
        Logger::getInstance()->debug(Mix_GetError());
    }
}

SoundManager::~SoundManager()
{
    Logger::getInstance()->debug("DESTRUYENDO SOUND MANAGER");
    if (this->sound != NULL)
    {
        Mix_Pause(1);
        Logger::getInstance()->debug("(SoundManager::Liberando chunk)");
        Mix_FreeChunk(this->sound);
        this->sound = NULL;
    }
    Logger::getInstance()->debug("(SoundManager::Cerrando audio)");
    Mix_CloseAudio();
}

void SoundManager::PlaySound(char* path)
{
    this->sound = Mix_LoadWAV(path);

    if (this->sound == NULL)
    {
        Logger::getInstance()->debug("(SoundManager::Error al ejecutar sonido)");
        Logger::getInstance()->debug(Mix_GetError());
    }
    else
    {
        Mix_PlayChannel(1, this->sound, 0);
    }
}

void SoundManager::PlayKickOffSound()
{
    /* SONIDO DE COMIENZO DE TIEMPO DE JUEGO */
    char* path = "src/client/sound/time_start_sound.wav";
    this->PlaySound(path);
}

void SoundManager::PlayPlayerSelectionSound()
{
    /* SONIDO DE CAMBIO DE JUGADOR SELECCIONADO */
    char* path = "src/client/sound/select_player.wav";
    this->PlaySound(path);
}

void SoundManager::PlayKickBallSound()
{
    /* SONIDO DE PATADA */
    char* path = "src/client/sound/kick_sound.wav";
    this->PlaySound(path);
}

void SoundManager::PlayGoalSound()
{
    /* SONIDO DE GOL */
    char* path = "src/client/sound/goal_sound.wav";
    this->PlaySound(path);
    while(IsPlayingSound())
    {
        // Espero a que termine la musica de gol, para que quede pausada la musica principal
        // del juego, si es que esta sonando
        Logger::getInstance()->debug("(SoundManager::Ejecutando musica de gol");
    }
}

void SoundManager::PlayTimeUpSound()
{
    /* SONIDO DE FIN DE TIEMPO */
    char* path = "src/client/sound/time_up_sound.wav";
    this->PlaySound(path);
}

bool SoundManager::IsPlayingSound()
{
    return Mix_Playing(1) != 0;
}
