#include "sound-manager.h"

Mix_Chunk* SoundManager::change_player_sound = NULL;

SoundManager::SoundManager()
{
    //ctor
}

SoundManager::~SoundManager()
{
    //dtor
}

void SoundManager::LoadResources() {
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
        Logger::getInstance()->error(Mix_GetError());
    } else {
        SoundManager::change_player_sound = Mix_LoadWAV( "src/sound/select_player.wav" );
        if (SoundManager::change_player_sound == NULL) {
            Logger::getInstance()->error(Mix_GetError());
        }
        Mix_Volume(1, MIX_MAX_VOLUME/8);
    }
}

void SoundManager::FreeResources() {
    Mix_FreeChunk( SoundManager::change_player_sound );
    Mix_CloseAudio();
}

void SoundManager::PlayPlayerSelectionSound() {

    if( Mix_PlayChannel( 1, SoundManager::change_player_sound, 0 ) == -1 ) {
        Logger::getInstance()->error(Mix_GetError());
    }
}

