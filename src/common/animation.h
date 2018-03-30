#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Animation
{
    public:
        Animation(std::string name, std::vector<SDL_Rect*> clips, float framesPerCicle = 1.0);
        virtual ~Animation();
        std::vector<SDL_Rect*> GetClips();
        SDL_Rect* NextClip();
    protected:
    private:
        int width;
		int height;
		std::string name;
		std::vector<SDL_Rect*> clips;
		int currentClip;
		float framesPerCicle;
};

#endif // ANIMATION_H
