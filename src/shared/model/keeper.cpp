#include "keeper.h"

Keeper::Keeper() { // @suppress("Class members should be properly initialized")
	this->state = KEEPER_STATE::STILL_KEEPER;
}

Keeper::~Keeper() {
	
}

void Keeper::SetTeam(Team* team) {
	this->team = team;
	Location* default_location = this->GetDefaultLocation();
	this->location = new Location(default_location->GetX(), default_location->GetY(), default_location->GetZ());
	this->circle = new Circle(HALO_RADIUS, new Location(this->location));
}

void Keeper::TryToCatchBall() {
	Ball* ball = this->GetTeam()->GetMatch()->GetBall();
	if (!ball->IsHeldByAnyKeeper()) {
		bool other_team_has_ball = (ball->GetPlayer() != NULL) && team != ball->GetPlayer()->GetTeam();
		if (this != ball->GetKeeper() && (other_team_has_ball || ball->IsFree())) {
			bool collides = ball->GetCircle()->ExistsCollision3d(this->circle);
			if (collides) {
				Trajectory* trajectory = new Trajectory(this);
				last_kick_request = std::chrono::system_clock::now();
				ball->SetTrajectory(trajectory);
			}
		}
	}
}

void Keeper::TryToKick() {
	if (this->HasBall()) {
		unsigned int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_kick_request).count();
		if (elapsed_millis > KICK_DELAY_MILLIS) {
			Ball* ball = this->GetTeam()->GetMatch()->GetBall();
			Trajectory* trajectory = new Trajectory(this->PlaysOnWestSide() ? DIRECTION::EAST : DIRECTION::WEST, 2, TRAJECTORY_TYPE::FLOOR);
			ball->SetTrajectory(trajectory);
			last_kick_request = std::chrono::system_clock::now();
			this->state = KEEPER_STATE::KICKING_KEEPER;
		}
	}
}

void Keeper::TryToStopKicking() {
	if (this->state == KEEPER_STATE::KICKING_KEEPER) {
		unsigned int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_kick_request).count();
		if (elapsed_millis > KICK_DELAY_MILLIS) {
			this->state = KEEPER_STATE::STILL_KEEPER;
		}
	}
}

bool Keeper::HasBall() {
	Ball* ball = this->GetTeam()->GetMatch()->GetBall();
	return ball->GetKeeper() != nullptr && this == ball->GetKeeper();
}

void Keeper::TryToRun() {
	if (this->state == KEEPER_STATE::STILL_KEEPER || this->state == KEEPER_STATE::MOVING_UP_KEEPER || this->state == KEEPER_STATE::MOVING_DOWN_KEEPER) {
		
		Ball* ball = this->GetTeam()->GetMatch()->GetBall();
		unsigned int ball_y = ball->GetLocation()->GetY();
		unsigned int keeper_y = this->GetLocation()->GetY();
		
		if (ball_y > keeper_y && keeper_y < (PITCH_Y_CENTER + KEEPER_Y_RANGE)) {
			this->state = KEEPER_STATE::MOVING_DOWN_KEEPER;
			this->location->UpdateY(location->GetY() + WALKING_SPEED);
			this->circle->Move(this->location);
		} else if (ball_y < keeper_y && keeper_y > (PITCH_Y_CENTER - KEEPER_Y_RANGE)) {
			this->state = KEEPER_STATE::MOVING_UP_KEEPER;
			this->location->UpdateY(location->GetY() - WALKING_SPEED);
			this->circle->Move(this->location);
		} else {
			this->state = KEEPER_STATE::STILL_KEEPER;
		}
	}
}

Team* Keeper::GetTeam() {
	return this->team;
}

bool Keeper::PlaysForTeamA() {
	return this->team->GetTeamNumber() == TEAM_NUMBER::TEAM_A;
}

Location* Keeper::GetDefaultLocation() {
	return this->team->GetFormation()->GetKeeperLocation();
}

void Keeper::SetLocation(Location* location) {
	this->location = location;
}

Location* Keeper::GetLocation() {
	return this->location;
}

bool Keeper::IsStill() {
	return this->state == KEEPER_STATE::STILL_KEEPER;
}
bool Keeper::IsMovingUp() {
	return this->state == KEEPER_STATE::MOVING_UP_KEEPER;
}
bool Keeper::IsMovingDown() {
	return this->state == KEEPER_STATE::MOVING_DOWN_KEEPER;
}
bool Keeper::IsKicking() {
	return this->state == KEEPER_STATE::KICKING_KEEPER;
}
bool Keeper::IsJumpingUp() {
	return this->state == KEEPER_STATE::JUMPING_UP_KEEPER;
}
bool Keeper::IsJumpingDown() {
	return this->state == KEEPER_STATE::JUMPING_DOWN_KEEPER;
}

KEEPER_STATE Keeper::GetState() {
	return this->state;
}

void Keeper::UpdateState(KEEPER_STATE state) {
	this->state = state;
}

bool Keeper::PlaysOnWestSide() {
	return this->location->GetX() < PITCH_X_CENTER;
}
