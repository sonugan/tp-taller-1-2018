#include "camera.h"
#include <unistd.h>

Camera::Camera(int pitch_width, int pitch_height, int width, int height, IShowable* showable, SDL_Renderer* renderer, Location* initialPosition)
{
    this->pitch_width = pitch_width;
    this->pitch_height = pitch_height;

    this->area = new SDL_Rect();
    this->area->x = initialPosition->GetX();
    this->area->y = initialPosition->GetY();

    this->area->w = width;
    this->area->h = height;

    this->showable = showable;
    this->renderer = renderer;
}

Camera::~Camera()
{
    std::cout << "Destructor de Camera" << "\n";
    delete this->area;
}

void Camera::Render()
{
    this->Move();
    this->views[0]->Render(this->area->x, this->area->y, this->area->w, this->area->h);
    for (unsigned int i = 0; i < this->views.size(); i++) {
        this->views[i]->Render(this->area->x, this->area->y, this->area->w, this->area->h);
    }
}

void Camera::SetLocatable(IShowable* showable)
{
    this->showable = showable;
}

void Camera::Add(AbstractView* view)
{
    this->views.push_back(view);
}

std::vector<AbstractView*> Camera::GetViews()
{
    return this->views;
}

void Camera::SetStartPosition(Location* position)
{
    this->area->x = position->GetX();
    this->area->y = position->GetY();
}

void Camera::Move()
{
    Location* location = this->showable->GetLocation();

    int x = location->GetX() + this->showable->GetWidth()/2;
    int y = location->GetY() + this->showable->GetHeight()/2;

    if(x <= this->area->x + CAMERA_MARGIN)
    {
        this->area->x -= (this->area->x + CAMERA_MARGIN) - x;
    }
    if(x >= (this->area->x + this->area->w) - CAMERA_MARGIN)
    {
        this->area->x += x - ((this->area->x + this->area->w) - CAMERA_MARGIN);
    }
    if(y <= this->area->y + CAMERA_MARGIN)
    {
        this->area->y -= (this->area->y + CAMERA_MARGIN) - y;
    }
    if(y >= (this->area->y + this->area->h) - CAMERA_MARGIN)
    {
        this->area->y += y - ((this->area->y + this->area->h) - CAMERA_MARGIN);
    }

    //Centrar el objecto en la camara
//    this->area->x = (location->GetX() + this->showable->GetWidth()/2) - this->area->w/2;
//    this->area->y = (location->GetY() + this->showable->GetHeight()/2)- this->area->h/2;

    //Keep the camera in bounds
    if( this->area->x < 0 )
    {
        this->area->x = 0;
    }

    if( this->area->y < 0 )
    {
        this->area->y = 0;
    }
    if( this->area->x > this->pitch_width - this->area->w )
    {
        this->area->x = this->pitch_width - this->area->w;
    }
    if( this->area->y > this->pitch_height - this->area->h )
    {
        this->area->y = this->pitch_height - this->area->h;
    }
}
