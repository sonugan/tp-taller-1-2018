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
	this->active_kickoff_team = TEAM_NUMBER::TEAM_A; // esto es arbitrario. cambiar si hace falta.
}

MatchState::~MatchState()
{}

MATCH_STATE_TYPE MatchState::GetType(){
	return this->type;
}

bool MatchState::IsKickOff() {
	return MATCH_STATE_TYPE::KICKOFF == GetType();
}

void MatchState::SetKickOff(TEAM_NUMBER active_kickoff_team) {
	this->type=MATCH_STATE_TYPE::KICKOFF;
	this->active_kickoff_team = active_kickoff_team;
}

void MatchState::SetPlaying() {
	this->type = MATCH_STATE_TYPE::PLAYING;
}

void MatchState::SetGoal(TEAM_NUMBER goal_scorer_team) {
	this->type = MATCH_STATE_TYPE::GOAL;
	this->goal_scorer_team = goal_scorer_team;
}

void MatchState::SetGoalKick(TEAM_NUMBER goal_kick_team) {
	this->type = MATCH_STATE_TYPE::GOAL_KICK;
	this->goal_kick_team = goal_kick_team;
}

void MatchState::SetTimeup() {
	this->type = MATCH_STATE_TYPE::TIME_UP;
}
