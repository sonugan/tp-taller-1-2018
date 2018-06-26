#include "rectangle.h"

Rectangle::Rectangle(int x1, int x2, int y1, int y2)
{
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
}

Rectangle::~Rectangle()
{

}

bool Rectangle::IsInside(Location* location)
{
    int x = location->GetX();
    int y = location->GetY();
    return x >= this->x1
        && x <= this->x2
        && y >= this->y1
        && y <= this->y2;
}
