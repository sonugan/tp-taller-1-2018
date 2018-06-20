#ifndef SRC_SHARED_MODEL_KEEPER_H_
#define SRC_SHARED_MODEL_KEEPER_H_

#include "team.h"
#include "location.h"
#include "trajectory.h"
#include "../collision/circle.h"

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
	void TryToRun();
	void TryToKick();
	void TryToStopKicking();
	bool HasBall();
	KEEPER_STATE GetState();
	void UpdateState(KEEPER_STATE state);
	bool PlaysOnWestSide();
private:
    std::chrono::time_point<std::chrono::system_clock> last_kick_request;
    static const unsigned int KICK_DELAY_MILLIS = 1000;
    static const unsigned int PITCH_Y_CENTER = 580;
    static const unsigned int PITCH_X_CENTER = 960;
	static const unsigned int KEEPER_Y_RANGE = 100;
	static const unsigned int HALO_RADIUS = 50;
	static const unsigned int WALKING_SPEED = 2;
	Team* team;
	Location* location;
	Location* GetDefaultLocation();
	KEEPER_STATE state;
	Circle* circle;
};

#endif /* SRC_SHARED_MODEL_KEEPER_H_ */
