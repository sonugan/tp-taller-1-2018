/*
 * match-state.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: swandelow
 */

#include "match-state.h"

MatchState::MatchState()
{
	this->type = MATCH_STATE_TYPE::KICKOFF;
}

MatchState::~MatchState()
{}

MATCH_STATE_TYPE MatchState::GetType(){
	return this->type;
}

bool MatchState::IsKickOff() {
	return MATCH_STATE_TYPE::KICKOFF == GetType();
}
