#include "animation.h"

Animation::Animation(std::string name, std::vector<SDL_Rect*> clips, float framesPerCicle)
{
    this->name = name;
    this->clips = clips;
    this->currentClip = 0;
    this->framesPerCicle = framesPerCicle;
}

Animation::~Animation()
{
    std::cout << "Destructor de Animation" << "\n";
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
    currentClip++;
    if((currentClip * framesPerCicle) >= clips.size())
    {
        currentClip = 0;
    }
    int currentClipIndex = currentClip * framesPerCicle;
    return clips[currentClipIndex];
}
