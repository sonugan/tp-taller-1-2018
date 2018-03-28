#include "camera.h"

Camera::Camera(int xStartPosition, int yStartPosition, int width, int height, IShowable* showable, SDL_Renderer* renderer)
{
    this->area = new SDL_Rect();
    this->area->x = xStartPosition;
    this->area->y = yStartPosition;
    this->area->w = width;
    this->area->h = height;

    this->showable = showable;
    this->area = new SDL_Rect();
    this->area->x = xStartPosition;
    this->area->y = yStartPosition;
    this->area->w = width;
    this->area->h = height;
    this->renderer = renderer;

    std::vector<SDL_Rect*> clips;
    clips.push_back(this->area);

    this->sprite_sheet = new SpriteSheet(this->renderer, "pitch.jpg", clips);
}

Camera::~Camera()
{
    std::cout << "Destructor de Camera" << "\n";
    delete this->area;
    //delete this->sprite_sheet; TODO
}

void Camera::Render()
{
    this->Move();
    sprite_sheet->Render(0, 0, this->area);

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

void Camera::Move()
{
    Location* location = this->showable->GetLocation();

    this->area->x = (location->GetX() + this->showable->GetWidth()/2) - 400;
    this->area->y = (location->GetY() + this->showable->GetHeight()/2)- 300;

    //Keep the camera in bounds
    if( this->area->x < 0 )
    {
        this->area->x = 0;
    }

    if( this->area->y < 0 )
    {
        this->area->y = 0;
    }
    if( this->area->x > 1920 - this->area->w )
    {
        this->area->x = 1920 - this->area->w;
    }
    if( this->area->y > 1080 - this->area->h )
    {
        this->area->y = 1080 - this->area->h;

    }
}
