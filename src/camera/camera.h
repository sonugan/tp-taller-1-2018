#ifndef CAMERA_H
#define CAMERA_H

#include "../common/abstract-view.h"
#include "../common/ishowable.h"

class Camera
{
    public:
        Camera(int xStartPosition, int yStartPosition, int width, int height, IShowable* showable, SDL_Renderer* renderer);
        virtual ~Camera();
        void Render();
        void SetLocatable(IShowable* showable);
        void Add(AbstractView* view);
        std::vector<AbstractView*> GetViews();
        SDL_Rect* area;
    protected:
    private:
        std::vector<AbstractView*> views;
        void Move();
        unsigned int width;
        unsigned int height;
        IShowable* showable;

        static const unsigned int MARGIN = 3;
        SDL_Texture* texture;

        SDL_Renderer* renderer;
        SpriteSheet* sprite_sheet;
};

#endif // CAMERA_H
