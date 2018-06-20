/*
 * position.h
 *
 *  Created on: Jun 15, 2018
 *      Author: swandelow
 */

#ifndef SRC_SHARED_MODEL_POSITION_H_
#define SRC_SHARED_MODEL_POSITION_H_

#include "location.h"

class Position
{
public:
	Position();
	Position(Location* default_location, Location* kickoff_location);
	virtual ~Position();

	Location* GetDefaultLocation();
	void SetDefaultLocation(Location* default_location);
	Location* GetKickoffLocation();
	void SetKickoffLocation(Location* kickoff_location);
private:
	Location* default_location = NULL;
	Location* kickoff_location = NULL;
	//TODO: agregar PositionArea
};

#endif /* SRC_SHARED_MODEL_POSITION_H_ */
