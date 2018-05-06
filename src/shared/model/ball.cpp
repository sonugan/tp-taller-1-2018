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

void Ball::SetTrajectory(Trajectory* new_trajectory) {
    std::cout << "Ball::SetTrajectory \n";
    Trajectory* old_trajectory = this->trajectory;
    this->trajectory = new_trajectory;
    if (old_trajectory != NULL) {
        std::cout << "Ball::SetTrajectory deleting old trajectory \n";
        delete old_trajectory;
        std::cout << "Ball::SetTrajectory old trajectory deleted \n";
    }
}

void Ball::Move() {
    if (this->trajectory != NULL) {
        this->trajectory->UpdateToNextLocation(this->location);
    }
}

bool Ball::IsFree() {
    return (this->trajectory == NULL) || (this->trajectory != NULL && this->trajectory->GetPlayer() == NULL);
}

Player* Ball::GetPlayer() {
    if (trajectory != NULL) {
        return trajectory->GetPlayer();
    }
    return NULL;
}
