/*
 * position.cpp
 *
 *  Created on: Jun 15, 2018
 *      Author: swandelow
 */

#include "position.h"

Position::Position()
{
	// TODO Auto-generated constructor stub

}

Position::Position(Location* default_location, Location* kickoff_location, Location* passive_kickoff_location) {
	this->default_location = default_location;
	this->kickoff_location = kickoff_location;
	this->passive_kickoff_location = passive_kickoff_location;
}

Position::~Position()
{
	delete default_location;
	delete kickoff_location;
}

Location* Position::GetDefaultLocation() {
	return this->default_location;
}

Location* Position::GetKickoffLocation() {
	return this->kickoff_location;
}

Location* Position::GetPassiveKickoffLocation() {
	return this->passive_kickoff_location;
}

void Position::SetPassiveKickoffLocation(Location* passive_kickoff_location) {
	this->passive_kickoff_location = passive_kickoff_location;
}
