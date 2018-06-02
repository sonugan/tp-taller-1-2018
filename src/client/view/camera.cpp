#include "camera.h"
#include <unistd.h>
#include "../../shared/logger.h"

Camera::Camera(int game_width, int game_height, int width, int height, IShowable* showable, SDL_Renderer* renderer, Location* initialPosition) {

    this->game_width = game_width;
    this->game_height = game_height;
    this->info_panel = new InfoPanelView();

    this->area = new SDL_Rect();
    this->area->x = initialPosition->GetX();
    this->area->y = initialPosition->GetY();

    this->area->w = width;
    this->area->h = height;

    this->showable = showable;
    this->renderer = renderer;
}

Camera::~Camera() {
    Logger::getInstance()->debug("DESTRUYENDO CAMARA");
    delete this->area;
}

void Camera::Render() {
    this->Move();

    for (unsigned int i = 0; i < this->views.size(); i++) {
        this->views[i]->Render(this->area->x, this->area->y, this->area->w, this->area->h);
    }

    this->info_panel->Render(0, 0, this->area->w, this->area->h);

    // Pongo las vistas de los mini players por separado, porque sino quedan tapadas por el menu
    for (unsigned int i = 0; i < this->mini_player_views.size(); i++) {
        this->mini_player_views[i]->Render(this->area->x, this->area->y, this->area->w, this->area->h);
    }
}

void Camera::SetShowable(IShowable* showable) {
    this->showable = showable;
    this->previous_showable_location = showable->GetLocation();
}

void Camera::Add(AbstractView* view) {
    this->views.push_back(view);
}

void Camera::AddMiniPlayerView(MiniPlayerView* view) {
    this->mini_player_views.push_back(view);
}

std::vector<AbstractView*> Camera::GetViews() {
    return this->views;
}

void Camera::SetStartPosition(Location* position) {
    this->area->x = position->GetX();
    this->area->y = position->GetY();
}

void Camera::Move() {
    Location* location = this->showable->GetLocation();

    if (this->showable->GetPreviousLocation()->Distance(this->showable->GetLocation()) > CAMERA_LOCATION_CHANGE_THRESHOLD) {
        previous_showable_location = this->showable->GetPreviousLocation();
    }

    int x = location->GetX();
    int y = location->GetY();

    //esto suaviza los cambios bruscos de la cámara
    if (previous_showable_location->GetX() > x) {
        x += (previous_showable_location->GetX()-x)/3;
    } else if (previous_showable_location->GetX() < x) {
        x -= (x-previous_showable_location->GetX())/3;
    }

    if (previous_showable_location->GetY() > y) {
        y += (previous_showable_location->GetY()-y)/3;
    } else if (previous_showable_location->GetY() < y) {
        y -= (y-previous_showable_location->GetY())/3;
    }
    previous_showable_location->UpdateX(x);
    previous_showable_location->UpdateY(y);

    if(x <= this->area->x + CAMERA_MARGIN) {
        this->area->x -= (this->area->x + CAMERA_MARGIN) - x;
    }
    if(x >= (this->area->x + this->area->w) - CAMERA_MARGIN) {
        this->area->x += x - ((this->area->x + this->area->w) - CAMERA_MARGIN);
    }
    if(y <= this->area->y + CAMERA_MARGIN) {
        this->area->y -= (this->area->y + CAMERA_MARGIN) - y;
    }
    if(y >= (this->area->y + this->area->h) - CAMERA_MARGIN) {
        this->area->y += y - ((this->area->y + this->area->h) - CAMERA_MARGIN);
    }

    //Centrar el objecto en la camara
    this->area->x = (x + this->showable->GetWidth()/2) - this->area->w/2;
    this->area->y = (y + this->showable->GetHeight()/2)- this->area->h/2;

    //Keep the camera in bounds
    if( this->area->x < 0 ) {
        this->area->x = 0;
    }
    if( this->area->y < 0 ) {
        this->area->y = 0;
    }
    if( this->area->x > this->game_width - this->area->w ) {
        this->area->x = this->game_width - this->area->w;
    }
    if( this->area->y > this->game_height - this->area->h ) {
        this->area->y = this->game_height - this->area->h;
    }

}


