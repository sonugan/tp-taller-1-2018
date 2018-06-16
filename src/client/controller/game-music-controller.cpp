#include "game-music-controller.h"

GameMusicController::GameMusicController(GameMusic* game_music)
{
    this->game_music = game_music;
    this->paused = false;
}

GameMusicController::~GameMusicController()
{
    //dtor
}

void GameMusicController::PauseMusic(const Uint8 *keyboard_state_array)
{
    if (keyboard_state_array[SDL_SCANCODE_P])
    {
        this->game_music->Pause();
        paused = true;
    }
}

void GameMusicController::ResumeMusic(const Uint8 *keyboard_state_array)
{
    if (keyboard_state_array[SDL_SCANCODE_M])
    {
        this->game_music->Resume();
        paused = false;
    }
}

void GameMusicController::Handle(const Uint8* keyboard_state_array)
{
    if (!this->paused)
    {
        PauseMusic(keyboard_state_array);
    }
    else
    {
        ResumeMusic(keyboard_state_array);
    }
}

