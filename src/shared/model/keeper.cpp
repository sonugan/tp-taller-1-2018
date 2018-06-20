#include "keeper.h"

Keeper::Keeper() { // @suppress("Class members should be properly initialized")
	this->state = KEEPER_STATE::STILL_KEEPER;
}

Keeper::~Keeper() {
	
}

void Keeper::SetTeam(Team* team) {
	this->team = team;
	Location* default_location = this->GetDefaultLocation();
	this->location = new Location(default_location->GetX(), default_location->GetY(), default_location->GetZ());
}

Team* Keeper::GetTeam() {
	return this->team;
}

bool Keeper::PlaysForTeamA() {
	return this->team->GetTeamNumber() == TEAM_NUMBER::TEAM_A;
}

Location* Keeper::GetDefaultLocation() {
	return this->team->GetFormation()->GetKeeperLocation();
}

void Keeper::SetLocation(Location* location) {
	this->location = location;
}

Location* Keeper::GetLocation() {
	return this->location;
}

bool Keeper::IsStill() {
	return this->state == KEEPER_STATE::STILL_KEEPER;
}
bool Keeper::IsMovingUp() {
	return this->state == KEEPER_STATE::MOVING_UP_KEEPER;
}
bool Keeper::IsMovingDown() {
	return this->state == KEEPER_STATE::MOVING_DOWN_KEEPER;
}
bool Keeper::IsKicking() {
	return this->state == KEEPER_STATE::KICKING_KEEPER;
}
bool Keeper::IsJumpingUp() {
	return this->state == KEEPER_STATE::JUMPING_UP_KEEPER;
}
bool Keeper::IsJumpingDown() {
	return this->state == KEEPER_STATE::JUMPING_DOWN_KEEPER;
}
