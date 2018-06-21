#include "player-defense-strategy.h"
#include <iostream>

PlayerDefenseStrategy::PlayerDefenseStrategy(Player* player)
{
    this->player = player;
    this->coin_flipper = new CoinFlipper();
}

PlayerDefenseStrategy::~PlayerDefenseStrategy()
{
    delete this->rectangle;
    delete this->coin_flipper;
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
                if(this->player->GetLocation()->Distance(ball->GetLocation()) < 10 //TODO: MAGIC NUMBER
                    && this->coin_flipper->FlipPorc(5,3) == COIN_RESULT::WIN)
                {
                    player->ChangeToRecover();
                }
                else
                {
                    player->GoTo(ball->GetLocation(), false);
                }
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
