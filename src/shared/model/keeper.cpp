#include "keeper.h"

Keeper::Keeper() { // @suppress("Class members should be properly initialized")
	// TODO Auto-generated constructor stub

}

Keeper::~Keeper() {
	// TODO Auto-generated destructor stub
}

void Keeper::SetTeam(Team* team) {
	this->team = team;
	Location* default_location = this->GetDefaultLocation();
	this->location = new Location(default_location->GetX(), default_location->GetY(), default_location->GetZ());
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

Team* Keeper::GetTeam()
{
    return this->team;
}
