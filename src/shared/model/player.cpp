#include "player.h"
#include "../logger.h"

Player::Player(unsigned int position_index, Team* team) // @suppress("Class members should be properly initialized")
{
    this->team = team;
    this->position_index = position_index;
    this->still_state = new PlayerStillState(this);
    this->move_state = new PlayerMoveState(this);
    this->kick_state = new PlayerKickState(this);
    this->recover_ball_state = new PlayerRecoverBallState(this);

    this->defense_strategy = new PlayerDefenseStrategy(this);
    this->atack_stategy = new PlayerAtackStrategy(this);
    this->strategy = this->defense_strategy;

    this->current_state = this->still_state;
    this->coin_flipper = new CoinFlipper();

    switch (team->GetTeamNumber())
    {
    case TEAM_NUMBER::TEAM_A:
        this->default_direction = DIRECTION::EAST;
        this->plays_for_team_a = true;
        break;
    case TEAM_NUMBER::TEAM_B:
        this->default_direction = DIRECTION::WEST;
        this->plays_for_team_a = false;
        break;
    }
    this->direction = this->default_direction;

    this->color = USER_COLOR::NO_COLOR;

}

Player::~Player()
{
    Logger::getInstance()->debug("DESTRUYENDO PLAYER");
    if(location != nullptr)
    {
        delete location;
    }
    if(previous_location != nullptr)
    {
        delete previous_location;
    }
    delete still_state;
    delete move_state;
    delete kick_state;
    delete recover_ball_state;
    delete circle;
    delete coin_flipper;
    delete atack_stategy;
    delete defense_strategy;
}

void Player::MoveLeft(bool run)
{
    this->current_state->MoveLeft(run);
}

void Player::MoveRight(bool run)
{
    this->current_state->MoveRight(run);
}

void Player::MoveUp(bool run)
{
    this->current_state->MoveUp(run);
}

void Player::MoveDown(bool run)
{
    this->current_state->MoveDown(run);
}

void Player::MoveUpToRight(bool run)
{
    this->current_state->MoveUpToRight(run);
}

void Player::MoveUpToLeft(bool run)
{
    this->current_state->MoveUpToLeft(run);
}

void Player::MoveDownToRight(bool run)
{
    this->current_state->MoveDownToRight(run);
}

void Player::MoveDownToLeft(bool run)
{
    this->current_state->MoveDownToLeft(run);
}

void Player::Kick()
{
    this->current_state->Kick();
}

void Player::RecoverBall()
{
    this->current_state->RecoverBall();
}

Location* Player::GetLocation()
{
    return location;
}

Rectangle* Player::GetDefenseArea()
{
    return team->GetFormation()->GetDefenseAreaForPlayer(position_index);
}

DIRECTION Player::GetDirection()
{
    return this->direction;
}

Location* Player::GetDefaultLocation()
{
    return team->GetFormation()->GetLocationForPlayer(position_index);
}

void Player::SetTeam(Team* team)
{
    this->team = team;
    this->circle = new Circle(HALO_RADIUS, new Location(this->location));
    this->defense_strategy->SetDefenseArea(this->GetDefenseArea());
}

unsigned int Player::GetPositionIndex()
{
    return this->position_index;
}

bool Player::HasBall()
{
    Player* player_with_ball = team->GetMatch()->GetBall()->GetPlayer();
    //return (player_with_ball != NULL) && (this->GetPositionIndex() == player_with_ball->GetPositionIndex()) && (this->GetTeam()->GetName() == player_with_ball->GetTeam()->GetName());
    return this == player_with_ball;
}

bool Player::IsSelected()
{
    return this->color != USER_COLOR::NO_COLOR;
}

void Player::GoBackToDefaultPosition()
{
    Location* default_location = team->GetFormation()->GetLocationForPlayer(position_index);

    int default_x = default_location->GetX();
    int x = location->GetX();
    int default_y = default_location->GetY();
    int y = location->GetY();
    if (x > default_x && y > default_y)
    {
        MoveUpToLeft(false);
    }
    else if (x < default_x && y > default_y)
    {
        MoveUpToRight(false);
    }
    else if (x < default_x && y < default_y)
    {
        MoveDownToRight(false);
    }
    else if (x > default_x && y < default_y)
    {
        MoveDownToLeft(false);
    }
    else if (x > default_x && y == default_y)
    {
        MoveLeft(false);
    }
    else if (x < default_x && y == default_y)
    {
        MoveRight(false);
    }
    else if (x == default_x && y > default_y)
    {
        MoveUp(false);
    }
    else if (x == default_x && y < default_y)
    {
        MoveDown(false);
    }
    else
    {
        direction = this->default_direction;
    }

    if (abs(default_y - location->GetY()) < PLAYER_SPEED)
    {
        location->UpdateY(default_location->GetY());
    }
    if (abs(default_x - location->GetX()) < PLAYER_SPEED)
    {
        location->UpdateX(default_location->GetX());
    }
}

void Player::GoTo(Location* destiny_location, bool run)
{
    int destiny_x = destiny_location->GetX();
    int x = this->location->GetX();
    int destiny_y = destiny_location->GetY();
    int y = this->location->GetY();
    if (x > destiny_x && y > destiny_y)
    {
        MoveUpToLeft(run);
    }
    else if (x < destiny_x && y > destiny_y)
    {
        MoveUpToRight(run);
    }
    else if (x < destiny_x && y < destiny_y)
    {
        MoveDownToRight(run);
    }
    else if (x > destiny_x && y < destiny_y)
    {
        MoveDownToLeft(run);
    }
    else if (x > destiny_x && y == destiny_y)
    {
        MoveLeft(run);
    }
    else if (x < destiny_x && y == destiny_y)
    {
        MoveRight(run);
    }
    else if (x == destiny_x && y > destiny_y)
    {
        MoveUp(run);
    }
    else if (x == destiny_x && y < destiny_y)
    {
        MoveDown(run);
    }

    if (abs(destiny_y - this->location->GetY()) < PLAYER_SPEED)
    {
        this->location->UpdateY(destiny_location->GetY());
    }
    if (abs(destiny_x - this->location->GetX()) < PLAYER_SPEED)
    {
        this->location->UpdateX(destiny_location->GetX());
    }
}


Team* Player::GetTeam()
{
    return this->team;
}

bool Player::IsKicking()
{
    return this->current_state->IsKicking();
}

bool Player::IsStill()
{
    return location->GetX() == previous_location->GetX() &&
        location->GetY() == previous_location->GetY();
}
bool Player::IsMoving()
{
    return !this->GetIsStill();
}

bool Player::IsRecoveringBall()
{
    return this->current_state->IsRecoveringBall();
}

void Player::Move(bool run, bool jog)
{
    int speed;
    if (this->IsRecoveringBall())
    {
        speed = PLAYER_SPEED * 0.3;
    }
    else if (run)
    {
        speed = PLAYER_RUNNING_SPEED;
    }
    else if(jog)
    {
        speed = PLAYER_JOGGIN_SPEED;
    }
    else
    {
        speed = PLAYER_SPEED;
    }
    this->previous_location->Update(this->location->GetX(), this->location->GetY(), this->location->GetZ());
    Location* new_location = new Location(this->location);
    switch(direction)
    {
    case DIRECTION::NORTH:
        new_location->UpdateY(location->GetY() - speed);
        break;
    case DIRECTION::WEST:
        new_location->UpdateX(location->GetX() - speed);
        break;
    case DIRECTION::SOUTH:
        new_location->UpdateY(location->GetY() + speed);
        break;
    case DIRECTION::EAST:
        new_location->UpdateX(location->GetX() + speed);
        break;
    case DIRECTION::NORTHEAST:
        new_location->UpdateY(location->GetY() - speed);
        new_location->UpdateX(location->GetX() + speed);
        break;
    case DIRECTION::NORTHWEST:
        new_location->UpdateY(location->GetY() - speed);
        new_location->UpdateX(location->GetX() - speed);
        break;
    case DIRECTION::SOUTHEAST:
        new_location->UpdateY(location->GetY() + speed);
        new_location->UpdateX(location->GetX() + speed);
        break;
    case DIRECTION::SOUTHWEST:
        new_location->UpdateY(location->GetY() + speed);
        new_location->UpdateX(location->GetX() - speed);
        break;
    }

    this->location->Update(new_location);
    this->circle->Move(this->location);

    delete new_location;
}

void Player::PassBall(Location* nearestPlayer)
{
    if (HasBall())
    {
        Trajectory* trajectory = new Trajectory(direction, 2, TRAJECTORY_TYPE::FLOOR, nearestPlayer);
        team->GetMatch()->GetBall()->SetTrajectory(trajectory);
    }
}

void Player::PassBallTo(Player* player)
{
    int my_x = this->location->GetX();
    int my_y = this->location->GetY();
    int x = player->location->GetX();
    int y = player->location->GetY();

    if(abs(my_x - x) <= 15)
    {
        //direction = my_y <= y ? DIRECTION::SOUTH : DIRECTION::NORTH;
        direction = my_y <= y ? DIRECTION::SOUTH : DIRECTION::NORTH;
    }
    else if(abs(my_y - y) <= 15)
    {
        direction = my_x <= x ? DIRECTION::EAST : DIRECTION::WEST;
    }
    else if(abs(my_x - x) > 15)
    {
        if(my_x > x)
        {
            direction = my_y <= y ? DIRECTION::SOUTHWEST : DIRECTION::NORTHWEST;
        }
        else
        {
            direction = my_y <= y ? DIRECTION::SOUTHEAST : DIRECTION::NORTHEAST;
        }
    }
    PassBall(player->GetLocation());
}

void Player::KickBall(int power)
{
    if (HasBall())
    {
        Trajectory* trajectory = new Trajectory(direction, power, TRAJECTORY_TYPE::FLOOR);
        team->GetMatch()->GetBall()->SetTrajectory(trajectory);
    }
}

void Player::LongPass(int power, TRAJECTORY_TYPE trajectory_type)
{
    if (HasBall())
    {
        Trajectory* trajectory = new Trajectory(direction, power, trajectory_type);
        team->GetMatch()->GetBall()->SetTrajectory(trajectory);
    }
}

bool Player::PlaysForTeamA()
{
    return this->plays_for_team_a;
}

void Player::SetPlayerColor(USER_COLOR color)
{
    this->color = color;
}

void Player::SetDirection(DIRECTION direction)
{
    this->direction = direction;
}

USER_COLOR Player::GetPlayerColor()
{
    return this->color;
}

void Player::ChangeToMove()
{
    this->current_state = this->move_state;
}
void Player::ChangeToKick()
{
    this->current_state = this->kick_state;
}
void Player::ChangeToRecover()
{
    //if(!this->HasBall())
    //{
        this->current_state = this->recover_ball_state;
    //}
}
void Player::ChangeToPass()
{

}
void Player::ChangeToCatchBall()
{

}
void Player::ChangeToStill()
{
    //if(!this->HasBall())
    //{
        this->current_state = this->still_state;
    //}
}

void Player::Play()
{
    if(this->GetLocation() != nullptr && !position_has_been_initialized)
    {
        InitializePosition();
        position_has_been_initialized = true;
    }
    this->current_state->Play();
}

PLAYER_ACTION Player::GetCurrentAction()
{
    return this->current_state->GetName();
}

void Player::SetCurrentAction(PLAYER_ACTION action)
{
    switch (action) {
        case PLAYER_ACTION::PLAYER_IS_KICKING:
            this->current_state = kick_state;
            break;
        case PLAYER_ACTION::PLAYER_IS_RECOVERING:
            this->current_state = recover_ball_state;
            break;
        case PLAYER_ACTION::PLAYER_IS_RUNNING:
            this->current_state = move_state;
            break;
        default:
            this->current_state = still_state;
            break;
    }
}

void Player::SetIsStill(bool is_still)
{
    this->is_still = is_still;
}

bool Player::GetIsStill()
{
    return this->is_still;
}

void Player::SetLocation(Location* location)
{
    this->location->Update(location->GetX(), location->GetY(), location->GetZ());
    this->previous_location->Update(location->GetX(), location->GetY(), location->GetZ());
}

Circle* Player::GetCircle()
{
    return this->circle;
}

bool Player::AreInSameTeam(Player* player)
{
    return player != nullptr && player->GetTeam() == this->GetTeam();
}

bool Player::TryRecover()
{
    Ball* ball = this->GetTeam()->GetMatch()->GetBall();
    if(ball->IsFree() && ball->GetCircle()->ExistsCollision3d(this->GetCircle()))
    {
        Trajectory* trajectory = new Trajectory(this);
        ball->SetTrajectory(trajectory);
        left_ball_counter = 30;
        return true;
    }
    else
    {
        if(left_ball_counter == 0)
        {
            if(!this->HasBall() && !ball->IsHeldByAnyKeeper()
                && !this->AreInSameTeam(ball->GetPlayer())
                && ball->GetCircle()->ExistsCollision3d(this->GetCircle())) //faltó esto!
            {
                if(coin_flipper->Win(100, 70))
                {
                    Trajectory* trajectory = new Trajectory(this);
                    ball->SetTrajectory(trajectory);
                    left_ball_counter = 30;
                    return true;
                }
            }
        }
        else
        {
            left_ball_counter--;
        }
    }
    return false;
}

IPlayerStrategy* Player::GetStrategy()
{
    return this->strategy;
}

void Player::NotifyChangeBall(Ball* ball)
{
    if(this->GetTeam()->HasBall() && ball->IsHeldByAnyPlayer())
    {
        this->strategy = this->atack_stategy;
        return;
    }
    this->strategy = this->defense_strategy;
}

bool Player::IsTeamA()
{
    Team* team_a = this->GetTeam()->GetMatch()->GetTeamA();
    return this->GetTeam() == team_a;
}

void Player::InitializePosition()
{
    this->is_defender = DefineDefender();
    this->is_forward = DefineForward();
    this->is_north_winger = DefineNorthWinger();
    this->is_south_winger = DefineSouthWinger();
    this->is_center = !is_south_winger && !is_north_winger;//TODO
}

bool Player::DefineForward()
{
    Location* location = this->GetLocation();
    vector<Player*> buddies = this->GetTeam()->GetPlayers();
    for(int i = 0; i < buddies.size(); i++)
    {
        Player* buddy = buddies[i];
        if(buddy != this)
        {
            if((IsTeamA() && buddy->GetLocation()->GetX() < this->GetLocation()->GetX())
                || (!IsTeamA() && buddy->GetLocation()->GetX() > this->GetLocation()->GetX()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Player::DefineDefender()
{
    Location* location = this->GetLocation();
    vector<Player*> buddies = this->GetTeam()->GetPlayers();
    for(int i = 0; i < buddies.size(); i++)
    {
        Player* buddy = buddies[i];
        if(buddy != this)
        {
            if((IsTeamA() && buddy->GetLocation()->GetX() > this->GetLocation()->GetX())
                || (!IsTeamA() && buddy->GetLocation()->GetX() < this->GetLocation()->GetX()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Player::DefineNorthWinger()
{
    Location* location = this->GetLocation();
    vector<Player*> buddies = this->GetTeam()->GetPlayers();
    for(int i = 0; i < buddies.size(); i++)
    {
        Player* buddy = buddies[i];
        if(buddy != this)
        {
            if(this->GetTeam()->GetFormation()->GetValue() == FORMATION::F_3_3)
            {
                if(buddy->GetLocation()->GetY() > this->GetLocation()->GetY())
                {
                    return false;
                }
            }
            else if(this->GetTeam()->GetFormation()->GetValue() == FORMATION::F_3_1_2
                || this->GetTeam()->GetFormation()->GetValue() == FORMATION::F_3_2_1)
            {
                if(!((IsTeamA() && buddy->GetLocation()->GetX() > this->GetLocation()->GetX())
                    || (!IsTeamA() && buddy->GetLocation()->GetX() < this->GetLocation()->GetX())) ||
                    buddy->GetLocation()->GetY() > this->GetLocation()->GetY())
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Player::DefineSouthWinger()
{
    Location* location = this->GetLocation();
    vector<Player*> buddies = this->GetTeam()->GetPlayers();
    for(int i = 0; i < buddies.size(); i++)
    {
        Player* buddy = buddies[i];
        if(buddy != this)
        {
            if(this->GetTeam()->GetFormation()->GetValue() == FORMATION::F_3_3)
            {
                if(buddy->GetLocation()->GetY() < this->GetLocation()->GetY())
                {
                    return false;
                }
            }
            else if(this->GetTeam()->GetFormation()->GetValue() == FORMATION::F_3_1_2
                || this->GetTeam()->GetFormation()->GetValue() == FORMATION::F_3_2_1)
            {
                if(!((IsTeamA() && buddy->GetLocation()->GetX() > this->GetLocation()->GetX())
                    || (!IsTeamA() && buddy->GetLocation()->GetX() < this->GetLocation()->GetX())) ||
                    buddy->GetLocation()->GetY() > this->GetLocation()->GetY())
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Player::IsForward()
{
    return this->is_forward;
}
bool Player::IsDefender()
{
    return this->is_defender;
}
bool Player::IsSouthWinger()
{
    return this->is_south_winger;
}
bool Player::IsNorthWinger()
{
    return this->is_north_winger;
}
bool Player::IsCenter()
{
    return this->is_center;
}
void Player::SetInitialLocation(Location* initial_location)
{
	this->location = new Location(initial_location->GetX(), initial_location->GetY(), initial_location->GetZ());
	this->previous_location = new Location(this->location->GetX(), this->location->GetY(), this->location->GetZ());
}

void Player::UpdatePlayerSide()
{
    if (this->team->GetTeamNumber() == TEAM_NUMBER::TEAM_A)
    {
        this->default_direction = DIRECTION::EAST;
    }
    else
    {
        this->default_direction = DIRECTION::WEST;
    }
    this->direction = this->default_direction;
}

bool Player::TeamScored() {
	bool is_goal = this->GetTeam()->GetMatch()->GetMatchState()->IsGoal();
	if (is_goal) {
		Match* match = this->GetTeam()->GetMatch();
		Team* scorer_team = match->GetTeamByNumber(match->GetMatchState()->GetGoalScorerTeam());
		return scorer_team == this->GetTeam();
	}
    return false;
}
