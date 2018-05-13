#include "ball.h"

Ball::Ball() {
    this->location = new Location(200, 200, 0);
    this->previous_location = new Location(200, 200, 0);
    this->trajectory = new Trajectory(DIRECTION::EAST, 0);
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
    //std::cout << "Ball::SetTrajectory \n";
    Trajectory* old_trajectory = this->trajectory;
    this->trajectory = new_trajectory;
    if (old_trajectory != NULL) {
        //std::cout << "Ball::SetTrajectory deleting old trajectory \n";
        delete old_trajectory;
        //std::cout << "Ball::SetTrajectory old trajectory deleted \n";
    }
    if (this->trajectory->GetPlayer() == NULL) {
        this->last_freed = std::chrono::system_clock::now();
    }
}

bool Ball::LastFreedDelayPassed() {
    unsigned int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>
                             (std::chrono::system_clock::now()-last_freed).count();

    return elapsed_millis > LAST_FREED_DELAY_MILLIS;
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
