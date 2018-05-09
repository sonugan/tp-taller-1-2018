#include "ball.h"

Ball::Ball() {
    this->location = new Location(200, 200, 0);
    this->previous_location = new Location(200, 200, 0);
}

Ball::~Ball() {
    delete location;
    delete previous_location;
}

Location* Ball::GetLocation() {
    return location;
}

Location* Ball::GetPreviousLocation() {
    return previous_location;
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
        this->previous_location->Update(this->location->GetX(), this->location->GetY(), this->location->GetZ());
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
