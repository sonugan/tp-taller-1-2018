#ifndef CAMERA_H
#define CAMERA_H

#include "../common/abstract-view.h"
#include "../common/ishowable.h"

class Camera
{
    public:
        Camera(int pitchWidth, int pitchHeight, int width, int height, IShowable* showable, SDL_Renderer* renderer);
        virtual ~Camera();
        void Render();
        void SetLocatable(IShowable* showable);
        void Add(AbstractView* view);
        std::vector<AbstractView*> GetViews();
        SDL_Rect* area;
        void SetStartPosition(Location* position);//Move the camera to this position
    protected:
    private:
        std::vector<AbstractView*> views;
        void Move();
        IShowable* showable;
        SDL_Renderer* renderer;
        unsigned int pitchHeight;
        unsigned int pitchWidth;
};

#endif // CAMERA_H
