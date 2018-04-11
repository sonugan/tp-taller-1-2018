#ifndef CAMERA_H
#define CAMERA_H

#include "../common/abstract-view.h"
#include "../common/ishowable.h"

class Camera
{
    public:
        Camera(int pitch_width, int pitch_height, int width, int height, IShowable* showable, SDL_Renderer* renderer, Location* initialPosition);
        virtual ~Camera();
        void Render();
        void SetLocatable(IShowable* showable);
        void Add(AbstractView* view);
        std::vector<AbstractView*> GetViews();
        SDL_Rect* area;
        void SetStartPosition(Location* position);//Move the camera to this position
        const static int CAMERA_MARGIN = 100;

    protected:
    private:
        std::vector<AbstractView*> views;
        void Move();
        IShowable* showable;
        SDL_Renderer* renderer;
        unsigned int pitch_height;
        unsigned int pitch_width;
};

#endif // CAMERA_H
