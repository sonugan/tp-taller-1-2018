/*
 * match-state.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: swandelow
 */

#include "match-state.h"
#include "../logger.h"

MatchState::MatchState()
{
	this->SetKickOff(TEAM_NUMBER::TEAM_A);
}

MatchState::~MatchState()
{}

MATCH_STATE_TYPE MatchState::GetType(){
	return this->type;
}

MATCH_STATE_TYPE MatchState::GetPreviousType() {
	return this->previous_type;
}

// USAR SOLO PARA DESERIALIZAR
void MatchState::SetType(MATCH_STATE_TYPE type) {
	this->type = type;
}

bool MatchState::IsKickOff() {

	return MATCH_STATE_TYPE::KICKOFF == GetType();
}

void MatchState::SetKickOff(TEAM_NUMBER kicker_team) {
	Logger::getInstance()->debug("(MatchState:SetKickOff) Seteando kickoff state");
	this->previous_type = this->type;
	this->type=MATCH_STATE_TYPE::KICKOFF;
	this->kicker_team = kicker_team;
	this->state_start_time = chrono::system_clock::now();
}

void MatchState::SetPlaying() {
	Logger::getInstance()->debug("(MatchState:SetPlaying) Seteando playing state");
	this->previous_type = this->type;
	this->type = MATCH_STATE_TYPE::PLAYING;
}

bool MatchState::IsPlaying() {
	return MATCH_STATE_TYPE::PLAYING == GetType();
}

void MatchState::SetGoal(TEAM_NUMBER goal_scorer_team) {
	Logger::getInstance()->debug("(MatchState:SetGoal) Seteando goal state");
	this->previous_type = this->type;
	this->type = MATCH_STATE_TYPE::GOAL;
	this->goal_scorer_team = goal_scorer_team;
	this->state_start_time = chrono::system_clock::now();
}

void MatchState::SetGoalKick(TEAM_NUMBER goal_kick_team) {
	Logger::getInstance()->debug("(MatchState:SetGoalKick) Seteando goalkick state");
	this->previous_type = this->type;
	this->type = MATCH_STATE_TYPE::GOAL_KICK;
	this->goal_kick_team = goal_kick_team;
	this->state_start_time = chrono::system_clock::now();
}

void MatchState::SetTimeup() {
	Logger::getInstance()->debug("(MatchState:SetTimeup) Seteando timeup state");
	this->previous_type = this->type;
	this->type = MATCH_STATE_TYPE::TIME_UP;
	this->state_start_time = chrono::system_clock::now();
}

bool MatchState::IsReadyToChange() {
	if(MATCH_STATE_TYPE::PLAYING == GetType()) {
		return true;
	} else {
		unsigned int elapsed_seconds = chrono::duration_cast<chrono::seconds>(chrono::system_clock::now()- this->state_start_time).count();
		return elapsed_seconds > this->STATE_DURATION;
	}
}

TEAM_NUMBER MatchState::GetGoalScorerTeam() {
	return this->goal_scorer_team;
}

void MatchState::SetFinished() {
	Logger::getInstance()->debug("(MatchState:SetFinished) Seteando finished state");
	this->previous_type = this->type;
	this->type = MATCH_STATE_TYPE::FINISHED;
}

