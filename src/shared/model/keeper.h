#ifndef SRC_SHARED_MODEL_KEEPER_H_
#define SRC_SHARED_MODEL_KEEPER_H_

#include "team.h"
#include "location.h"

class Keeper {
public:
	Keeper();
	virtual ~Keeper();
	void SetTeam(Team* team);
	void SetLocation(Location* location);
	Location* GetLocation();
private:
	Team* team;
	Location* location;
	Location* GetDefaultLocation();
};

#endif /* SRC_SHARED_MODEL_KEEPER_H_ */
