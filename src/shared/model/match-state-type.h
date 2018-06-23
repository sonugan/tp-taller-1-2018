/*
 * match-state.h
 *
 *  Created on: Jun 10, 2018
 *      Author: swandelow
 */

#ifndef SRC_SHARED_MODEL_MATCH_STATE_TYPE_H_
#define SRC_SHARED_MODEL_MATCH_STATE_TYPE_H_


enum MATCH_STATE_TYPE {
	FINISHED,
	GOAL,
	GOAL_KICK,
	KICKOFF,
	PLAYING,
	TIME_UP,
	WAITING_TO_START
};


#endif /* SRC_SHARED_MODEL_MATCH_STATE_TYPE_H_ */
