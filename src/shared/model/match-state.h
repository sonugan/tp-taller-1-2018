/*
 * match-state.h
 *
 *  Created on: Jun 11, 2018
 *      Author: swandelow
 */

#ifndef SRC_SHARED_MODEL_MATCH_STATE_H_
#define SRC_SHARED_MODEL_MATCH_STATE_H_

#include "match-state-type.h"
#include "team-number.h"

class MatchState
{
public:
	MatchState();
	virtual ~MatchState();
	MATCH_STATE_TYPE GetType();

	void SetKickOff(TEAM_NUMBER active_kickoff_team);
	bool IsKickOff();
	void SetPlaying();
	void SetGoal(TEAM_NUMBER goal_scorer_team);
	void SetGoalKick(TEAM_NUMBER goal_kick_team);
	void SetTimeup();

private:
	MATCH_STATE_TYPE type;
	TEAM_NUMBER active_kickoff_team;
	TEAM_NUMBER goal_scorer_team;
	TEAM_NUMBER goal_kick_team;
};

#endif /* SRC_SHARED_MODEL_MATCH_STATE_H_ */
