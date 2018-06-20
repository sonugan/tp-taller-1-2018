/*
 * match-state.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: swandelow
 */

#include "match-state.h"

MatchState::MatchState()
{
	this->SetKickOff(TEAM_NUMBER::TEAM_A);
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
	this->state_start_time = chrono::system_clock::now();
}

void MatchState::SetPlaying() {
	this->type = MATCH_STATE_TYPE::PLAYING;
}

void MatchState::SetGoal(TEAM_NUMBER goal_scorer_team) {
	this->type = MATCH_STATE_TYPE::GOAL;
	this->goal_scorer_team = goal_scorer_team;
	this->state_start_time = chrono::system_clock::now();
}

void MatchState::SetGoalKick(TEAM_NUMBER goal_kick_team) {
	this->type = MATCH_STATE_TYPE::GOAL_KICK;
	this->goal_kick_team = goal_kick_team;
	this->state_start_time = chrono::system_clock::now();
}

void MatchState::SetTimeup() {
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
	this->type = MATCH_STATE_TYPE::FINISHED;
}

