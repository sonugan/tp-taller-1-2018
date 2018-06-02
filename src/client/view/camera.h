#ifndef CAMERA_H
#define CAMERA_H

#include "abstract-view.h"
#include "ishowable.h"
#include "mini-player-view.h"
#include "player-view.h"
#include "info-panel-view.h"
#include <map>

class PlayerView;
class MiniPlayerView;

class Camera
{
    public:
        Camera(int game_width, int game_height, int width, int height, IShowable* showable, SDL_Renderer* renderer, Location* initialPosition);
        virtual ~Camera();
        void Render();
        void SetShowable(IShowable* showable);
        void Add(AbstractView* view);
        void AddMiniPlayerView(MiniPlayerView* view);
        std::vector<AbstractView*> GetViews();
        SDL_Rect* area;
        void SetStartPosition(Location* position);
        const static unsigned int CAMERA_MARGIN = 100;
        const static unsigned int CAMERA_LOCATION_CHANGE_THRESHOLD = 10;

    protected:
    private:
        std::vector<AbstractView*> views;
        std::vector<MiniPlayerView*> mini_player_views;
        void Move();
        IShowable* showable;
        Location* previous_showable_location;
        InfoPanelView* info_panel;
        SDL_Renderer* renderer;
        unsigned int game_height;
        unsigned int game_width;
};

#endif // CAMERA_H
