/*
 * match-state.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: swandelow
 */

#include "match-state.h"

MatchState::MatchState()
{
	this->type = MATCH_STATE_TYPE::WAITING_TO_START;
}

MatchState::~MatchState()
{}

MATCH_STATE_TYPE MatchState::GetType(){
	return this->type;
}
