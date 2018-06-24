#include "player-atack-strategy.h"

PlayerAtackStrategy::PlayerAtackStrategy(Player* player)
{
    Logger::getInstance()->debug("CREANDO PlayerAtackStrategy");
    this->player = player;
    this->coin_flipper = new CoinFlipper();
}

PlayerAtackStrategy::~PlayerAtackStrategy()
{
    Logger::getInstance()->debug("DESTRUYENDO PlayerAtackStrategy");
    if(this->vision_area != nullptr)
        delete this->vision_area;
    delete this->coin_flipper;
}

void PlayerAtackStrategy::Play()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::Play");
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
                if(!RecoverInAtack() && !RunToArea() && !StayDefend() && Convoy())
                    return;
            }
            else
            {
                if(!PassBall() && !Kick() && !RunWithBall())
                {
                    /*Location* goal_line = nullptr;
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
                    player->GoTo(goal_line, false);*/
                }
            }
        }
    }
}

bool PlayerAtackStrategy::PassBall()//TODO: los angulos de pase son de 45°, lo que hace que no todos los pases sean efectivos
                                    // reduciendose su efectividad cuanto mayor es la distancia
{
    Logger::getInstance()->debug("PlayerAtackStrategy::PassBall");
    if(!this->coin_flipper->Win(10,5)) return false;
    vector<Player*> pass_ball_players;
    vector<Player*> buddies = this->player->GetTeam()->GetPlayers();
    for(int i = 0; i < buddies.size(); i++)
    {
        Player* buddy = buddies[i];
        if(buddy != this->player)
        {
            float distance = buddy->GetLocation()->Distance(this->player->GetLocation());
            if(IsNearGoalLine(buddy) && distance <= 250)
            {
                pass_ball_players.push_back(buddy);
            }
        }
    }
    if(pass_ball_players.size() > 0)
    {
        int i = this->coin_flipper->GetNumber(pass_ball_players.size());
        if(i >= 0 && i < pass_ball_players.size())
        {
            this->player->PassBallTo(pass_ball_players[i]);
            return true;
        }
    }
    return false;

    /*if(this->coin_flipper->FlipPorc(10, 6) == COIN_RESULT::WIN)
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
    return false;*/
}

vector<Player*> PlayerAtackStrategy::GetEnemies()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::GetEnemies");
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
    Logger::getInstance()->debug("PlayerAtackStrategy::IsNearGoalLine");
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
    Logger::getInstance()->debug("PlayerAtackStrategy::IsPlayerInFrontOfMe");
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

bool PlayerAtackStrategy::ThereIsAnEnemyInFrontOfMe()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::ThereIsAnEnemyInFrontOfMe");
    vector<Player*> enemies = GetEnemies();
    for(int i = 0; i < enemies.size(); i++)
    {
        Player* enemy = enemies[i];
        int my_x = this->player->GetLocation()->GetX();
        int my_y = this->player->GetLocation()->GetY();
        int x = enemy->GetLocation()->GetX();
        int y = enemy->GetLocation()->GetY();
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
    Logger::getInstance()->debug("PlayerAtackStrategy::IsTeamA");
    if(this->player->GetTeam() != nullptr &&
        this->player->GetTeam()->GetMatch() != nullptr)
        {
        Team* team_a = this->player->GetTeam()->GetMatch()->GetTeamA();
        return this->player->GetTeam() == team_a;
    }
    return false;
}

bool PlayerAtackStrategy::AreBetween(int a, int b, int value)
{
    return abs(a - b) <= value;
}

bool PlayerAtackStrategy::Kick()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::Kick");
    if(IsOutisideShootingRange())
    {
        return false;
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
    Logger::getInstance()->debug("PlayerAtackStrategy::Cross");
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
    Logger::getInstance()->debug("PlayerAtackStrategy::IsInGoalZone");
    int x = this->player->GetLocation()->GetX();
    int y = this->player->GetLocation()->GetY();
    if(IsTeamA())
    {
        return x >= TEAM_A_GOAL_ZONE_X;// && y >= 252 && y <= 790;
    }
    else
    {
        return x <= TEAM_B_GOAL_ZONE_X;// && y >= 252 && y <= 790;
    }
}

bool PlayerAtackStrategy::IsInEnemyMiddle()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::IsInEnemyMiddle");
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
    Logger::getInstance()->debug("PlayerAtackStrategy::IsOutisideShootingRange");
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

bool PlayerAtackStrategy::IsBallInMyMiddle()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::IsBallInMyMiddle");
    Ball* ball = this->player->GetTeam()->GetMatch()->GetBall();
    if(IsTeamA())
    {
        return ball->GetLocation()->GetX() < 960;
    }
    else
    {
        return ball->GetLocation()->GetX() > 960;
    }
}

bool PlayerAtackStrategy::IsRecovering(){ return is_recovering; }

bool PlayerAtackStrategy::LongKick()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::LongKick");
    //x = 960 es el centro
    int distance_to_middle = abs(MIDDLE - this->player->GetLocation()->GetX());
    float inc = IsInGoalZone() ? 0.7 : 0.05;
    return this->coin_flipper->FlipPorc(100, 5 + distance_to_middle*inc) == COIN_RESULT::WIN;
}

bool PlayerAtackStrategy::MediumKick()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::MediumKick");
    int distance_to_middle = abs(MIDDLE - this->player->GetLocation()->GetX());
    float inc = IsInGoalZone() ? 0.7 : 0.05;
    return this->coin_flipper->FlipPorc(100, 2 + distance_to_middle*inc) == COIN_RESULT::WIN;
}

bool PlayerAtackStrategy::IsKeeperInFrontOfMe(Keeper* keeper)
{
    Logger::getInstance()->debug("PlayerAtackStrategy::IsKeeperInFrontOfMe");
    int my_x = this->player->GetLocation()->GetX();
    int my_y = this->player->GetLocation()->GetY();
    int x = keeper->GetLocation()->GetX();
    int y = keeper->GetLocation()->GetY();
    return AreBetween(my_y, y, WIDTH);
}

Keeper* PlayerAtackStrategy::GetOpponetKeeper()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::GetOpponetKeeper");
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
    Logger::getInstance()->debug("PlayerAtackStrategy::Point");
    int x = this->player->GetLocation()->GetX();
    int y = this->player->GetLocation()->GetY();
    Keeper* keeper = GetOpponetKeeper();

    if(IsTeamA())
    {
        if(y > GOAL_POST_NORTH && y < GOAL_POST_SOUTH)
        {
            if(!IsKeeperInFrontOfMe(keeper) || !IsInGoalZone())
                this->player->SetDirection(this->coin_flipper->Win(3,1)? DIRECTION::NORTHEAST :
                    (this->coin_flipper->Win(3,1) ? DIRECTION::SOUTHEAST : DIRECTION::EAST));
            else
            {
                this->player->SetDirection(this->coin_flipper->Win(2,1)? DIRECTION::SOUTHEAST : DIRECTION::NORTHEAST);
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
            this->player->SetDirection(this->coin_flipper->Win(3,1)? DIRECTION::NORTHWEST :
                (this->coin_flipper->Win(3,1) ? DIRECTION::SOUTHWEST : DIRECTION::WEST));
            else
            {
                this->player->SetDirection(this->coin_flipper->Win(2,1)? DIRECTION::SOUTHWEST : DIRECTION::NORTHWEST);
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

bool PlayerAtackStrategy::RecoverInAtack()//TODO: no detecta la pelota libre?¡
{
    Logger::getInstance()->debug("PlayerAtackStrategy::RecoverInAtack");
    Ball* ball = this->player->GetTeam()->GetMatch()->GetBall();
    Location* ball_location = ball->GetLocation();
    if(BallIsFree())
    {
        vector<Player*> buddies = this->player->GetTeam()->GetPlayers();
        int my_distance = ball_location->Distance(this->player->GetLocation());
        for(int i = 0; i < buddies.size(); i++)
        {
            Player* buddy = buddies[i];
            if(buddy != this->player)
            {
                float distance = ball_location->Distance(buddy->GetLocation());
                if(my_distance > distance)// || buddy->GetStrategy()->IsRecovering())
                {
                    is_recovering = false;
                    return false;
                }
            }
        }
        Location* destination = new Location(ball_location->GetX(), ball_location->GetY(), ball_location->GetZ());
        player->GoTo(destination, true);
        is_recovering = true;
        return true;
    }
    is_recovering = false;
    return false;
}

bool PlayerAtackStrategy::RunWithBall()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::RunWithBall");
    if(IsInGoalZone())
    {
        return false;
    }

    int prob = 100;
    if(this->player->IsDefender()) prob = 60;
    bool run = coin_flipper->Win(100, prob);

    Location* location = this->player->GetLocation();
    Location* destination = nullptr;

    int y = location->GetY();
    if(ThereIsAnEnemyInFrontOfMe() && this->coin_flipper->Win(3,2))
    {
        y += (this->coin_flipper->Win(2,1)? 10 : -10);
    }

    if(IsTeamA()) destination = new Location(TEAM_A_GOAL_ZONE_X + 150, y, location->GetZ());
    else destination = new Location(TEAM_B_GOAL_ZONE_X - 150, y, location->GetZ());

    this->player->GoTo(destination, run);
    return true;
}

bool PlayerAtackStrategy::RunToArea()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::RunToArea");
    if(IsInGoalZone())
    {
        is_running_to_area = false;
        return false;
    }
    vector<Player*> buddies = this->player->GetTeam()->GetPlayers();
    for(int i = 0; i < buddies.size(); i++)
    {
        Player* buddy = buddies[i];
        if(buddy != this->player && buddy->GetStrategy()->IsRunningToArea())
        {
            is_running_to_area = false;
            return false;
        }
    }

    int prob = 1;
    if(this->player->IsSouthWinger() || this->player->IsNorthWinger())
    {
        if(this->player->IsDefender()) prob = 40;
        else prob = 70;
    }
    else if(this->player->IsCenter())
    {
        if(this->player->IsDefender()) prob = 30;
        else prob = 50;
    }
    if(coin_flipper->Win(100, prob))
    {
        Location* location = this->player->GetLocation();
        Location* destination = nullptr;
        if(IsTeamA()) destination = new Location(TEAM_A_GOAL_ZONE_X + 150, location->GetY(), location->GetZ());
        else destination = new Location(TEAM_B_GOAL_ZONE_X - 150, location->GetY(), location->GetZ());

        this->player->GoTo(destination, true);
        is_running_to_area = true;
        return true;
    }
    return false;
}

bool PlayerAtackStrategy::StayDefend()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::StayDefend");
    int prob = 1;
    if(this->player->IsDefender())
    {
        if(IsInEnemyMiddle()) prob = 30;
        else prob = 100;
    }
    return !coin_flipper->Win(100, prob);
}

bool PlayerAtackStrategy::Convoy()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::Convoy");
    int prob = 100;
    if(this->player->IsDefender())
    {
        if(IsInEnemyMiddle()) prob = 60;
        else prob = 30;
    }

    if(coin_flipper->Win(100, prob) && !IsPlayerInFrontOfMe())
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
            return true;
        }
    }
    return false;
}

bool PlayerAtackStrategy::BallIsFree()
{
    Logger::getInstance()->debug("PlayerAtackStrategy::BallIsFree");
    vector<Player*> buddies = this->player->GetTeam()->GetPlayers();
    for(int i = 0; i < buddies.size(); i++)
    {
        if(buddies[i]->HasBall()) return false;
    }

    vector<Player*> enemies = GetEnemies();
    for(int i = 0; i < enemies.size(); i++)
    {
        if(enemies[i]->HasBall()) return false;
    }
    return true;
}
