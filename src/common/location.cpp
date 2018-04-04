#include "location.h"
#include "logger.h"


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
    this->x = x;
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
