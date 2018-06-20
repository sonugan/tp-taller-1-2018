#include "player-defense-strategy.h"
#include <iostream>

PlayerDefenseStrategy::PlayerDefenseStrategy(Player* player)
{
    this->player = player;
}

PlayerDefenseStrategy::~PlayerDefenseStrategy()
{
    delete this->rectangle;
}

void PlayerDefenseStrategy::Play()
{
    if(!this->player->IsSelected())
    {
        Ball* ball = player->GetTeam()->GetMatch()->GetBall();
        Team* ball_team = nullptr;
        if(!ball->IsFree())
        {
            ball_team = ball->GetPlayer()->GetTeam();
        }
        if(ball_team == nullptr || ball_team != this->player->GetTeam())
        {
            if(this->rectangle->IsInside(ball->GetLocation()))
            {
                player->GoTo(ball->GetLocation(), false);
            }
            else
            {
                player->GoBackToDefaultPosition();
            }
        }
        if(player->HasBall())
        {
            player->GoBackToDefaultPosition();
        }
    }
}

void PlayerDefenseStrategy::SetDefenseArea(Rectangle* rectangle)
{
    this->rectangle = rectangle;
}
