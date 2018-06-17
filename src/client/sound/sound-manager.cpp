#include "sound-manager.h"

SoundManager::SoundManager()
{
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024) == -1)
    {
        Logger::getInstance()->debug("Error al abrir canal para sonido: ");
        Logger::getInstance()->debug(Mix_GetError());
    }
}

SoundManager::~SoundManager()
{
    Logger::getInstance()->debug("DESTRUYENDO SOUND MANAGER");
    if (this->sound != NULL)
    {
        Mix_FreeChunk(this->sound);
    }
    Mix_CloseAudio();
}

void SoundManager::PlaySound(char* path)
{
    this->sound = Mix_LoadWAV(path);

    if (this->sound == NULL)
    {
        Logger::getInstance()->debug("Error al generar sonido: ");
        Logger::getInstance()->debug(Mix_GetError());
    }
    else
    {
        Mix_PlayChannel(-1, this->sound, 0);
    }
}

void SoundManager::PlayGameTimeStartSound()
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



