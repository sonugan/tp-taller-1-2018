/*
 * match-state.h
 *
 *  Created on: Jun 10, 2018
 *      Author: swandelow
 */

#ifndef SRC_SHARED_MODEL_MATCH_STATE_H_
#define SRC_SHARED_MODEL_MATCH_STATE_H_


enum MATCH_STATE {
	CORNER,
	GOAL,
	GOAL_KICK,
	KICKOFF,
	PLAYING,
	TIME_UP,
	FINISHED,
	WAITING_TO_START
};


#endif /* SRC_SHARED_MODEL_MATCH_STATE_H_ */
