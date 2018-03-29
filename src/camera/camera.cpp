#include "camera.h"

Camera::Camera(int pitchWidth, int pitchHeight, int width, int height, IShowable* showable, SDL_Renderer* renderer)
{
    this->pitchWidth = pitchWidth;
    this->pitchHeight = pitchHeight;

    this->area = new SDL_Rect();
    this->area->x = 0;
    this->area->y = 0;

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

    this->area->x = (location->GetX() + this->showable->GetWidth()/2) - this->area->w/2;
    this->area->y = (location->GetY() + this->showable->GetHeight()/2)- this->area->h/2;

    //Keep the camera in bounds
    if( this->area->x < 0 )
    {
        this->area->x = 0;
    }

    if( this->area->y < 0 )
    {
        this->area->y = 0;
    }
    if( this->area->x > this->pitchWidth - this->area->w )
    {
        this->area->x = this->pitchWidth - this->area->w;
    }
    if( this->area->y > this->pitchHeight - this->area->h )
    {
        this->area->y = this->pitchHeight - this->area->h;
    }
}
