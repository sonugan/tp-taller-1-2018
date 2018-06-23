#include "ball.h"

Ball::Ball() {
    this->location = new Location(960, 618, 0);
    this->previous_location = new Location(200, 200, 0);
    this->trajectory = new Trajectory(DIRECTION::EAST, 0, TRAJECTORY_TYPE::FLOOR);
    this->circle = new Circle(HALO_RADIUS, new Location(this->location));
    this->last_owner_player_color = USER_COLOR::NO_COLOR;
    this->last_owner_team = NULL;
}

Ball::~Ball() {
    delete location;
    delete previous_location;
    delete circle;
}

Location* Ball::GetLocation() {
    return location;
}

Location* Ball::GetPreviousLocation() {
    return previous_location;
}

Trajectory* Ball::GetTrajectory()
{
    return this->trajectory;
}

void Ball::SetTrajectory(Trajectory* new_trajectory) {
    Trajectory* old_trajectory = this->trajectory;
    this->trajectory = new_trajectory;
    if (old_trajectory != NULL) {
        delete old_trajectory;
    }
    if (this->trajectory->GetPlayer() == NULL) {
        this->last_freed = std::chrono::system_clock::now();
        Logger::getInstance()->debug("(Ball::SetTrajectory) PASE");
    }
}

bool Ball::LastFreedDelayPassed() {
    unsigned int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>
                             (std::chrono::system_clock::now()-last_freed).count();

    return elapsed_millis > LAST_FREED_DELAY_MILLIS;
}

void Ball::Move() {
    if (this->trajectory != NULL) {
        this->previous_location->Update(this->location->GetX(), this->location->GetY(), this->location->GetZ());
        this->trajectory->UpdateToNextLocation(this->location);
        this->circle->Move(this->location);
    }
}

bool Ball::IsFree() {
    return (this->trajectory == NULL) || (this->trajectory != NULL && this->trajectory->GetPlayer() == NULL);
}

Player* Ball::GetPlayer() {
    if (trajectory != NULL) {
        return trajectory->GetPlayer();
    }
    return NULL;
}

Keeper* Ball::GetKeeper() {
    if (trajectory != NULL) {
        return trajectory->GetKeeper();
    }
    return NULL;
}

bool Ball::IsHeldByAnyKeeper() {
	return GetKeeper() != NULL;
}


Circle* Ball::GetCircle()
{
    return this->circle;
}

void Ball::SetLastOwner(Team* team, USER_COLOR color)
{
    this->last_owner_team = team;
    this->last_owner_player_color = color;
}

USER_COLOR Ball::GetLastOwnerColor()
{
    return this->last_owner_player_color;
}

Team* Ball::GetLastOwnerTeam()
{
    return this->last_owner_team;
}

void Ball::ReturnToMiddle()
{
	Logger::getInstance()->debug("Ball::ReturnToMiddle");
    delete this->location;
    delete this->previous_location;
    this->location = new Location(960, 618, 0);
    this->previous_location = new Location(200, 200, 0);
    //Eliminando la trayectoria de la pelota
    delete this->trajectory;
    this->trajectory = new Trajectory(DIRECTION::EAST, 0, TRAJECTORY_TYPE::FLOOR);
    this->circle->Move(this->location);


    this->last_owner_team = NULL;
    this->last_owner_player_color = USER_COLOR::NO_COLOR;
}

void Ball::BounceOnThrowIn()
{
    if (this->trajectory == NULL)
    {
        return;
    }

    switch(this->trajectory->GetDirection())
    {
        case DIRECTION::NORTH:
        {
            this->trajectory->UpdateDirection(DIRECTION::SOUTH);
            break;
        }
        case DIRECTION::SOUTH:
        {
            this->trajectory->UpdateDirection(DIRECTION::NORTH);
            break;
        }
        case DIRECTION::NORTHEAST:
        {
            this->trajectory->UpdateDirection(DIRECTION::SOUTHEAST);
            break;
        }
        case DIRECTION::SOUTHEAST:
        {
            this->trajectory->UpdateDirection(DIRECTION::NORTHEAST);
            break;
        }
        case DIRECTION::NORTHWEST:
        {
            this->trajectory->UpdateDirection(DIRECTION::SOUTHWEST);
            break;
        }
        case DIRECTION::SOUTHWEST:
        {
            this->trajectory->UpdateDirection(DIRECTION::NORTHWEST);
            break;
        }
        default:
        {
            //La direccion no se actualiza
            return;
        }
    }

    //Desacelero un poco la pelota
    this->trajectory->UpdateBallSpeed(0.7*this->trajectory->GetBallSpeed());
}

void Ball::GoToKeeper(Keeper* keeper)
{
	Logger::getInstance()->debug("Ball::Going to keeper");
	Trajectory* keeper_trajectory = new Trajectory(keeper);
	this->SetTrajectory(keeper_trajectory);
    delete this->location;
    delete this->previous_location;
    this->location = new Location(keeper->GetLocation());
    this->previous_location = new Location(keeper->GetLocation());
    keeper->TryToKickOff();
}

void Ball::BounceOnGoalPost()
{
    if (this->trajectory == NULL)
    {
        return;
    }

    switch(this->trajectory->GetDirection())
    {
        case DIRECTION::NORTH:
        {
            this->trajectory->UpdateDirection(DIRECTION::SOUTH);
            break;
        }
        case DIRECTION::SOUTH:
        {
            this->trajectory->UpdateDirection(DIRECTION::NORTH);
            break;
        }
        case DIRECTION::NORTHEAST:
        {
            this->trajectory->UpdateDirection(DIRECTION::SOUTHEAST);
            break;
        }
        case DIRECTION::SOUTHEAST:
        {
            this->trajectory->UpdateDirection(DIRECTION::NORTHEAST);
            break;
        }
        case DIRECTION::NORTHWEST:
        {
            this->trajectory->UpdateDirection(DIRECTION::SOUTHWEST);
            break;
        }
        case DIRECTION::SOUTHWEST:
        {
            this->trajectory->UpdateDirection(DIRECTION::NORTHWEST);
            break;
        }
        case DIRECTION::EAST:
        {
            this->trajectory->UpdateDirection(DIRECTION::WEST);
            break;
        }
        case DIRECTION::WEST:
        {
            this->trajectory->UpdateDirection(DIRECTION::EAST);
            break;
        }
        default:
        {
            //La direccion no se actualiza
            return;
        }
    }

    //Desacelero un poco la pelota
    this->trajectory->UpdateBallSpeed(0.85*this->trajectory->GetBallSpeed());
}

bool Ball::IsGoingToWestGoalZone() {
	DIRECTION trajectory_direction = this->trajectory->GetDirection();
	bool west_direction = DIRECTION::WEST == trajectory_direction || DIRECTION::SOUTHWEST == trajectory_direction || DIRECTION::NORTHWEST == trajectory_direction; 
	if (west_direction && location->GetX() < 500 && location->GetY() > 300 && location->GetY() < 858) {
		unsigned int ball_speed = this->trajectory->GetBallSpeed();
		return (ball_speed > 50) && IsFree(); 
	}
	return false;
}

bool Ball::IsGoingToEastGoalZone() {
	DIRECTION trajectory_direction = this->trajectory->GetDirection();
	bool west_direction = DIRECTION::EAST == trajectory_direction || DIRECTION::SOUTHEAST == trajectory_direction || DIRECTION::NORTHEAST == trajectory_direction; 
	if (west_direction && location->GetX() > 1420 && location->GetY() > 300 && location->GetY() < 858) {
		unsigned int ball_speed = this->trajectory->GetBallSpeed();
		return (ball_speed > 50) && IsFree(); 
	}
	return false;
}
