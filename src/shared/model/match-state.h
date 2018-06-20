/*
 * match-state.h
 *
 *  Created on: Jun 11, 2018
 *      Author: swandelow
 */

#ifndef SRC_SHARED_MODEL_MATCH_STATE_H_
#define SRC_SHARED_MODEL_MATCH_STATE_H_

#include "match-state-type.h"

class MatchState
{
public:
	MatchState();
	virtual ~MatchState();
	MATCH_STATE_TYPE GetType();

	bool IsKickOff();
private:
	MATCH_STATE_TYPE type;
};

#endif /* SRC_SHARED_MODEL_MATCH_STATE_H_ */
