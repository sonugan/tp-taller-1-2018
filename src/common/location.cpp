#include "location.h"

Location::Location(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
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

    this->y = y;

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
