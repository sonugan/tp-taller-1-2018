#include "ball.h"

Ball::Ball() {
    this->location = new Location(960, 540, 0);
    this->previous_location = new Location(200, 200, 0);
    this->trajectory = new Trajectory(DIRECTION::EAST, 0);
    this->last_owner_player_color = USER_COLOR::NO_COLOR;
    this->last_owner_team = NULL;
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
    Trajectory* old_trajectory = this->trajectory;
    this->trajectory = new_trajectory;
    if (old_trajectory != NULL) {
        delete old_trajectory;
    }
    if (this->trajectory->GetPlayer() == NULL) {
        this->last_freed = std::chrono::system_clock::now();
        Logger::getInstance()->debug("(Ball::SetTrajectory) PASE");
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

void Ball::SetLastOwner(Team* team, USER_COLOR color)
{
    this->last_owner_team = team;
    this->last_owner_player_color = color;
}

USER_COLOR Ball::GetLastOwnerColor()
{
    return this->last_owner_player_color;
}

Team* Ball::GetLastOwnerTeam()
{
    return this->last_owner_team;
}

void Ball::ReturnToMiddle()
{
    delete this->location;
    delete this->previous_location;
    this->location = new Location(960, 540, 0);
    this->previous_location = new Location(200, 200, 0);
    //Eliminando la trayectoria de la pelota
    delete this->trajectory;
    this->trajectory = new Trajectory(DIRECTION::EAST, 0);

    this->last_owner_team = NULL;
    this->last_owner_player_color = USER_COLOR::NO_COLOR;
}
