#ifndef CAMERA_H
#define CAMERA_H

#include "abstract-view.h"
#include "ishowable.h"
#include "player-view.h"
#include <map>

class PlayerView;
class Camera
{
    public:
        Camera(int pitch_width, int pitch_height, int width, int height, IShowable* showable, SDL_Renderer* renderer, Location* initialPosition);
        virtual ~Camera();
        void Render();
        void SetShowable(IShowable* showable);
        void Add(AbstractView* view);
        std::vector<AbstractView*> GetViews();
        SDL_Rect* area;
        void SetStartPosition(Location* position);
        const static unsigned int CAMERA_MARGIN = 100;
        const static unsigned int CAMERA_LOCATION_CHANGE_THRESHOLD = 10;

    protected:
    private:
        std::vector<AbstractView*> views;
        void Move();
        IShowable* showable;
        Location* previous_showable_location;
        SDL_Renderer* renderer;
        unsigned int pitch_height;
        unsigned int pitch_width;
};

#endif // CAMERA_H
