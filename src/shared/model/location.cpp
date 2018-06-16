#include "location.h"
#include "../logger.h"


Location::Location(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Location::Location(Location* location)
{
    this->x = location->x;
    this->y = location->y;
    this->z = location->z;
}

Location::~Location() {}

int Location::GetX() {
    return x;
}

int Location::GetY() {
    return y;
}

int Location::GetZ() {
    return z;
}

void Location::Update(int x, int y, int z) {

    // Controlo que el jugador no se pase de los limites de la cancha

    if (x >= MIN_X_LOCATION && x <= MAX_X_LOCATION) {
        this->x = x;

    } else if (x < MIN_X_LOCATION) {
        this->x = MIN_X_LOCATION;

    } else if (x > MAX_X_LOCATION) {
        this->x = MAX_X_LOCATION;
    }

    if (y >= MIN_Y_LOCATION && y <= MAX_Y_LOCATION) {
        this->y = y;

    } else if (y < MIN_Y_LOCATION) {
        this->y = MIN_Y_LOCATION;

    } else if (y > MAX_Y_LOCATION) {
        this->y = MAX_Y_LOCATION;
    }

    this->z = z;
}

void Location::UpdateX(int x) {
    Update(x, GetY(), GetZ());
}

void Location::UpdateY(int y) {
    Update(GetX(), y, GetZ());
}

void Location::UpdateZ(int z) {
    Update(GetX(), GetY(), z);
}

void Location::Update(Location* location)
{
    this->x = location->x;
    this->y = location->y;
    this->z = location->z;
}

float Location::Distance(Location* other_location) {
    return sqrt(pow((x - other_location->GetX()), 2)
               + pow((y - other_location->GetY()), 2)
                     + pow((z - other_location->GetZ()), 2));
}

float Location::ManhattanDistance(Location* other_location)
{
    return abs(this->x - other_location->x)
            + abs(this->y - other_location->y)
                + abs(this->z - other_location->z);
}

std::string Location::ToString() {
    return "x: " + to_string(x) + ", y: " + to_string(y) + ", z: " + to_string(z);
}
