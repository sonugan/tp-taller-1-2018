#include "circle.h"

Circle::Circle(int radius, Location* center)
{
    this->radius = radius;
    this->center = center;
}

Circle::~Circle()
{
    delete this->center;
}

bool Circle::ExistsCollision2d(Circle* other_circle)
{
    return ExistsCollision3d(other_circle);
}

bool Circle::ExistsCollision3d(Circle* other_circle)
{
    int distance = this->center->Distance(other_circle->center);
    int radius_sum = this->radius + other_circle->radius;
    return distance <= radius_sum;
}

void Circle::Move(Location* location)
{
    this->center->Update(location);
}

Location* Circle::GetCenter()
{
    return this->center;
}
