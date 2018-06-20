#include "player-atack-strategy.h"

PlayerAtackStrategy::PlayerAtackStrategy(Player* player)
{
    this->player = player;
}

PlayerAtackStrategy::~PlayerAtackStrategy()
{
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
                Location* destination = new Location(player_ball_location->GetX(), location->GetY(), location->GetZ());
                player->GoTo(destination, false);
                //delete destination; //TODO: revisar
            }
            else
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
