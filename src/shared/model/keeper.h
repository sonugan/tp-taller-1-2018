#ifndef SRC_SHARED_MODEL_KEEPER_H_
#define SRC_SHARED_MODEL_KEEPER_H_

#include "team.h"
#include "location.h"

enum class KEEPER_STATE {STILL_KEEPER, MOVING_UP_KEEPER, MOVING_DOWN_KEEPER, KICKING_KEEPER, JUMPING_UP_KEEPER, JUMPING_DOWN_KEEPER };
class Team;
class Keeper {
public:
	Keeper();
	virtual ~Keeper();
	void SetTeam(Team* team);
	Team* GetTeam();
	void SetLocation(Location* location);
	Location* GetLocation();
	bool PlaysForTeamA();
	bool IsStill();
	bool IsMovingUp();
	bool IsMovingDown();
	bool IsKicking();
	bool IsJumpingUp();
	bool IsJumpingDown();
	void TryToCatchBall();
private:
	Team* team;
	Location* location;
	Location* GetDefaultLocation();
	KEEPER_STATE state;
};

#endif /* SRC_SHARED_MODEL_KEEPER_H_ */
