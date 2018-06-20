/*
 * match-state.h
 *
 *  Created on: Jun 11, 2018
 *      Author: swandelow
 */

#ifndef SRC_SHARED_MODEL_MATCH_STATE_H_
#define SRC_SHARED_MODEL_MATCH_STATE_H_

#include <chrono>
#include "match-state-type.h"
#include "team-number.h"

using namespace std;

class MatchState
{
public:
	MatchState();
	virtual ~MatchState();
	MATCH_STATE_TYPE GetType();
	// USAR SOLO EN CLIENT PARA DESERIALIZAR
	void SetType(MATCH_STATE_TYPE type);

	void SetKickOff(TEAM_NUMBER active_kickoff_team);
	bool IsKickOff();
	void SetPlaying();
	void SetGoal(TEAM_NUMBER goal_scorer_team);
	void SetGoalKick(TEAM_NUMBER goal_kick_team);
	void SetTimeup();
	bool IsReadyToChange();
	TEAM_NUMBER GetGoalScorerTeam();
	void SetFinished();


private:
	MATCH_STATE_TYPE type;
	TEAM_NUMBER active_kickoff_team;
	TEAM_NUMBER goal_scorer_team;
	TEAM_NUMBER goal_kick_team;
	const unsigned int STATE_DURATION = 2; // en segundos
	chrono::time_point<chrono::system_clock> state_start_time;
};

#endif /* SRC_SHARED_MODEL_MATCH_STATE_H_ */
