#include "rectangle.h"

Rectangle::Rectangle(Location* leftmost_highest_point, int height, int base)
{
    this->leftmost_highest_point = leftmost_highest_point;
    this->height = height;
    this->base = base;
}

Rectangle::~Rectangle()
{
    delete this->leftmost_highest_point;
}

bool Rectangle::IsInside(Location* location)
{
    int x = location->GetX();
    int y = location->GetY();
    return x >= this->leftmost_highest_point->GetX()
        && x <= this->leftmost_highest_point->GetX() + this->base
        && y >= this->leftmost_highest_point->GetY()
        && y <= this->leftmost_highest_point->GetY() + this->height;
}

void Rectangle::Move(Location* location)
{
    this->leftmost_highest_point->Update(location);
}

Location* Rectangle::GetLeftmostHighestPoint()
{
    return this->leftmost_highest_point;
}
