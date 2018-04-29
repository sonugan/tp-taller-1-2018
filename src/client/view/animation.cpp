#include "animation.h"
#include "../../shared/logger.h"

Animation::Animation(std::string name, std::vector<SDL_Rect*> clips, float frames_per_cicle)
{
    this->name = name;
    this->clips = clips;
    this->current_clip = 0;
    this->frames_per_cicle = frames_per_cicle;
}

Animation::~Animation()
{
    Logger::getInstance()->debug("DESTRUYENDO ANIMACION");
    for (unsigned int i = 0; i < clips.size(); i++) {
        delete (clips[i]);
    }
    clips.clear();
}

std::vector<SDL_Rect*> Animation::GetClips()
{
    return this->clips;
}

SDL_Rect* Animation::NextClip()
{
    current_clip++;
    if((current_clip * frames_per_cicle) >= clips.size())
    {
        current_clip = 0;
    }
    unsigned int current_clip_index = current_clip * frames_per_cicle;
    return clips[current_clip_index];
}

void Animation::Restart()
{
    current_clip = 0;
}
