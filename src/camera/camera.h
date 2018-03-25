#ifndef CAMERA_H
#define CAMERA_H

#include "../common/abstract-view.h"
#include "../common/ishowable.h"

class Camera : public AbstractView
{
    public:
        Camera(int xStartPosition, int yStartPosition, int width, int height, IShowable* showable, SDL_Renderer* renderer);
        virtual ~Camera();
        void Render();
        void  SetLocatable(IShowable* showable);
    protected:
    private:
        void Move();
        unsigned int width;
        unsigned int height;
        IShowable* showable;
        SDL_Rect* area;
        static const unsigned int MARGIN = 3;
        SDL_Texture* texture;
};

#endif // CAMERA_H
