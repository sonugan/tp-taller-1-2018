#include "player-atack-strategy.h"

PlayerAtackStrategy::PlayerAtackStrategy(Player* player)
{
    this->player = player;
    this->coin_flipper = new CoinFlipper();
}

PlayerAtackStrategy::~PlayerAtackStrategy()
{
    if(this->vision_area != nullptr)
        delete this->vision_area;
    delete this->coin_flipper;
}

void PlayerAtackStrategy::Play()
{
    if(this->vision_area == nullptr)
    {
        if(player->GetLocation() != nullptr)
            this->vision_area = new Circle(80, player->GetLocation());
        else
            return;
    }
    if(!player->IsSelected())
    {
        if(this->player->GetTeam()->HasBall())
        {
            if(!player->HasBall())
            {
                if(!IsPlayerInFrontOfMe())
                {
                    Ball* ball = player->GetTeam()->GetMatch()->GetBall();
                    Location* player_ball_location = ball->GetPlayer()->GetLocation();
                    Location* location = player->GetLocation();
                    Team* team_a = player->GetTeam()->GetMatch()->GetTeamA();
                    Location* destination = new Location(player_ball_location->GetX(), location->GetY(), location->GetZ());
                    if((player->GetTeam() == team_a && destination->GetX() >= location->GetX())
                        || (player->GetTeam() != team_a && destination->GetX() <= location->GetX()))
                    {
                        player->GoTo(destination, false);
                    }
                }
                //delete destination; //TODO: revisar
            }
            else
            {
                if(!Kick() && !PassBall())
                //if(!PassBall())
                {
                    Location* goal_line = nullptr;
                    Team* team_a = player->GetTeam()->GetMatch()->GetTeamA();
                    if(player->GetTeam() == team_a)
                    {
                        goal_line = new Location(player->GetTeam()->GetTeamAGoalLine());
                    }
                    else
                    {
                        goal_line = new Location(player->GetTeam()->GetTeamBGoalLine());
                    }
                    if(goal_line != nullptr)
                    {
                        goal_line->UpdateY(player->GetLocation()->GetY());
                    }
                    player->GoTo(goal_line, false);
                }
            }
        }
    }
}

bool PlayerAtackStrategy::PassBall()
{
    if(this->coin_flipper->FlipPorc(10, 6) == COIN_RESULT::WIN)
    {
        vector<Player*> buddies = this->player->GetTeam()->GetPlayers();
        float min_distance = Location::MAX_DISTANCE;
        Player* pass_ball_player = nullptr;
        for(int i = 0; i < buddies.size(); i++)
        {
            Player* buddy = buddies[i];
            if(buddy != this->player)
            {
                if(IsNearGoalLine(buddy))// && buddy->GetCircle()->ExistsCollision2d(this->vision_area))
                {
                    float distance = buddy->GetLocation()->Distance(this->player->GetLocation());
                    if(distance < min_distance)
                    {
                        pass_ball_player = buddy;
                        min_distance = distance;
                    }
                }
            }
        }
        if(pass_ball_player != nullptr)
        {
            this->player->PassBallTo(pass_ball_player);
            return true;
        }
    }
    return false;
}

vector<Player*> PlayerAtackStrategy::GetEnemies()
{
    Team* team_a = player->GetTeam()->GetMatch()->GetTeamA();
    if(player->GetTeam() == team_a)
    {
        return player->GetTeam()->GetMatch()->GetTeamB()->GetPlayers();
    }
    else
    {
        return player->GetTeam()->GetMatch()->GetTeamA()->GetPlayers();
    }
}

bool PlayerAtackStrategy::IsNearGoalLine(Player* buddy)
{
    if(buddy != nullptr && buddy->GetTeam() != nullptr)
    {
        if(IsTeamA())
        {
            return buddy->GetLocation()->GetX() > this->player->GetLocation()->GetX();
        }
        else
        {
            return buddy->GetLocation()->GetX() < this->player->GetLocation()->GetX();
        }
    }
    return false;
}

bool PlayerAtackStrategy::IsPlayerInFrontOfMe()
{
    vector<Player*> buddies = player->GetTeam()->GetPlayers();
    for(int i = 0; i < buddies.size(); i++)
    {
        Player* buddy = buddies[i];
        int my_x = this->player->GetLocation()->GetX();
        int my_y = this->player->GetLocation()->GetY();
        int x = buddy->GetLocation()->GetX();
        int y = buddy->GetLocation()->GetY();
        if(IsTeamA())
        {
            if(my_x < x && x - my_x < 100 && AreBetween(my_y, y, WIDTH))
                return true;
        }
        else
        {
            if(my_x > x && my_x - x < 100 && AreBetween(my_y, y, WIDTH))
                return true;
        }
    }
    return false;
}

bool PlayerAtackStrategy::IsTeamA()
{
    Team* team_a = this->player->GetTeam()->GetMatch()->GetTeamA();
    return this->player->GetTeam() == team_a;
}

bool PlayerAtackStrategy::AreBetween(int a, int b, int value)
{
    return abs(a - b) <= value;
}

bool PlayerAtackStrategy::Kick()
{
    if(IsOutisideShootingRange())
    {
        return false;
    }
    if(IsInEnemyMiddle())
    {
        if(LongKick())
        {
            this->Point();
            this->player->PassBall();//TODO: KICK
            return true;
        }
        else if(MediumKick())
        {
            this->Point();
            this->player->PassBall();//TODO: KICK
            return true;
        }
    }
    if(IsInGoalZone())
    {
        Keeper* keeper = GetOpponetKeeper();
        if(IsKeeperInFrontOfMe(keeper))
        {
            if(this->coin_flipper->Flip() == COIN_RESULT::WIN)
            {
                this->player->MoveUp(false);
            }
            else
            {
                this->player->MoveDown(false);
            }
            return true;
        }
        else
        {
            if(LongKick())
            {
                this->Point();
                this->player->PassBall();//TODO: KICK
                return true;
            }
            else if(MediumKick())
            {
                this->Point();
                this->player->PassBall();//TODO: KICK
                return true;
            }
        }
    }
    return false;
}

bool PlayerAtackStrategy::Cross()
{
    if(IsOutisideShootingRange())
    {
        if(this->coin_flipper->FlipPorc(10, 8) == COIN_RESULT::WIN)
        {
            vector<Player*> buddies = this->player->GetTeam()->GetPlayers();
            Player* pass_ball_player = nullptr;

            for(int i = 0; i < buddies.size(); i++)
            {
                Player* buddy = buddies[i];
                if(buddy != this->player)
                {
                    if(IsExpectingACross(buddy))
                    {
                        pass_ball_player = buddy;
                        break;
                    }
                }
            }
            if(pass_ball_player != nullptr)
            {
                //this->player->CrossTo(pass_ball_player);
                return true;
            }
        }
    }
    return false;
}

bool PlayerAtackStrategy::IsInGoalZone()
{
    int x = this->player->GetLocation()->GetX();
    int y = this->player->GetLocation()->GetY();
    if(IsTeamA())
    {
        return x >= 1422;// && y >= 252 && y <= 790;
    }
    else
    {
        return x <= 492;// && y >= 252 && y <= 790;
    }
}

bool PlayerAtackStrategy::IsInEnemyMiddle()
{
    if(IsTeamA())
    {
        return this->player->GetLocation()->GetX() > MIDDLE;
    }
    else
    {
        return this->player->GetLocation()->GetX() < MIDDLE;
    }
}

bool PlayerAtackStrategy::IsOutisideShootingRange()
{
    int y = this->player->GetLocation()->GetY();
    if(y > GOAL_POST_SOUTH + 180 && y < GOAL_POST_NORTH - 180)
    {
        if(IsTeamA())
        {
            return this->player->GetLocation()->GetX() >= 1568;
        }
        else
        {
            return this->player->GetLocation()->GetX() <= 366;
        }
    }
    return false;
}

bool PlayerAtackStrategy::IsExpectingACross(Player* player)
{
    return false;
}

bool PlayerAtackStrategy::LongKick()
{
    //x = 960 es el centro
    int distance_to_middle = abs(MIDDLE - this->player->GetLocation()->GetX());
    float inc = IsInGoalZone() ? 0.1 : 0.08;
    return this->coin_flipper->FlipPorc(100, 5 + distance_to_middle*inc) == COIN_RESULT::WIN;
}

bool PlayerAtackStrategy::MediumKick()
{
    int distance_to_middle = abs(MIDDLE - this->player->GetLocation()->GetX());
    float inc = IsInGoalZone() ? 0.1 : 0.08;
    return this->coin_flipper->FlipPorc(100, 2 + distance_to_middle*inc) == COIN_RESULT::WIN;
}

bool PlayerAtackStrategy::IsKeeperInFrontOfMe(Keeper* keeper)
{
    int my_x = this->player->GetLocation()->GetX();
    int my_y = this->player->GetLocation()->GetY();
    int x = keeper->GetLocation()->GetX();
    int y = keeper->GetLocation()->GetY();
    return AreBetween(my_y, y, WIDTH);
}

Keeper* PlayerAtackStrategy::GetOpponetKeeper()
{
    if(IsTeamA())
    {
        return this->player->GetTeam()->GetMatch()->GetTeamA()->GetKeeper();
    }
    else
    {
        return this->player->GetTeam()->GetMatch()->GetTeamB()->GetKeeper();
    }
}

void PlayerAtackStrategy::Point()
{
    int x = this->player->GetLocation()->GetX();
    int y = this->player->GetLocation()->GetY();
    Keeper* keeper = GetOpponetKeeper();

    if(IsTeamA())
    {
        if(y > GOAL_POST_NORTH && y < GOAL_POST_SOUTH)
        {
            if(!IsKeeperInFrontOfMe(keeper) || !IsInGoalZone())
                this->player->SetDirection(DIRECTION::EAST);
            else
            {
                this->player->SetDirection(this->coin_flipper->Flip() == COIN_RESULT::WIN? DIRECTION::SOUTHEAST : DIRECTION::NORTHEAST);
            }
        }
        else if(y <= GOAL_POST_NORTH)
        {
            this->player->SetDirection(DIRECTION::SOUTHEAST);
        }
        else
        {
            this->player->SetDirection(DIRECTION::NORTHEAST);
        }
    }
    else
    {
        if(y > GOAL_POST_NORTH && y < GOAL_POST_SOUTH)
        {
            if(!IsKeeperInFrontOfMe(keeper) || !IsInGoalZone())
                this->player->SetDirection(DIRECTION::WEST);
            else
            {
                this->player->SetDirection(this->coin_flipper->Flip() == COIN_RESULT::WIN? DIRECTION::SOUTHWEST : DIRECTION::NORTHWEST);
            }
        }
        else if(y <= GOAL_POST_NORTH)
        {
            this->player->SetDirection(DIRECTION::SOUTHWEST);
        }
        else
        {
            this->player->SetDirection(DIRECTION::NORTHWEST);
        }
    }
}
