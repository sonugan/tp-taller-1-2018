#include "ball.h"

Ball::Ball()
{
    this->location = new Location(200, 200, 0);
}

Ball::~Ball()
{
    delete location;
}

Location* Ball::GetLocation() {
    return location;
}

void Ball::UpdateLocation(int x, int y, int z) {
    this->location->Update(x, y, z);
}
