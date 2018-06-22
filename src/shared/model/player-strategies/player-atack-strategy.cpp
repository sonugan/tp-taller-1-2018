#include "player-atack-strategy.h"

PlayerAtackStrategy::PlayerAtackStrategy(Player* player)
{
    this->player = player;
    this->vision_area = new Circle(80, player->GetLocation());
    this->coin_flipper = new CoinFlipper();
}

PlayerAtackStrategy::~PlayerAtackStrategy()
{
    delete this->coin_flipper;
}

void PlayerAtackStrategy::Play()
{
    if(!player->IsSelected())
    {
        if(this->player->GetTeam()->HasBall())
        {
            if(!player->HasBall())
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
                //delete destination; //TODO: revisar
            }
            else
            {
                //if(!this->PassBall())
                //{
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
                    //player->GoTo(goal_line, false);
                //}
            }
        }
    }
}

bool PlayerAtackStrategy::PassBall()
{
    /*if(this->coin_flipper->FlipPorc(10, 8) == COIN_RESULT::WIN)
    {
        vector<Player*> buddies = player->GetTeam()->GetPlayers();
        float min_distance = Location::MAX_DISTANCE;
        Player* pass_ball_player = nullptr;
        for(int i = 0; i < buddies.size(); i++)
        {
            Player* buddy = buddies[i];
            if(IsNearGoalLine(buddy) && buddy->GetCircle()->ExistsCollision2d(this->vision_area))
            {
                float distance = buddy->GetLocation()->Distance(this->player->GetLocation());
                if(distance < min_distance)
                {
                    pass_ball_player = buddy;
                    min_distance = distance;
                }
            }
        }
        if(pass_ball_player != nullptr)
        {
            this->player->PassBallTo(pass_ball_player);
            return true;
        }
    }*/
    return false;
}

vector<Player*> PlayerAtackStrategy::GetEnemies()
{
    /*Team* team_a = player->GetTeam()->GetMatch()->GetTeamA();
    if(player->GetTeam() == team_a)
    {
        return player->GetTeam()->GetMatch()->GetTeamB()->GetPlayers();
    }
    else
    {
        return player->GetTeam()->GetMatch()->GetTeamA()->GetPlayers();
    }*/
}

bool PlayerAtackStrategy::IsNearGoalLine(Player* player)
{
    /*Team* team_a = player->GetTeam()->GetMatch()->GetTeamA();
    if(player->GetTeam() == team_a)
    {
        return player->GetLocation()->GetX() >= this->player->GetLocation()->GetX();
    }
    else
    {
        return player->GetLocation()->GetX() <= this->player->GetLocation()->GetX();
    }*/
    return false;
}
