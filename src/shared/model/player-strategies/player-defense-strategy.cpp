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
        if(ball->IsHeldByAnyPlayer())
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

bool PlayerDefenseStrategy::KickBall()
{
    /*vector<Player*> enemies;
    Team* team_a = player->GetTeam()->GetMatch()->GetTeamA();
    if(player->GetTeam() == team_a)
    {
        enemies = player->GetTeam()->GetMatch()->GetTeamB()->GetPlayers();
    }
    else
    {
        enemies = player->GetTeam()->GetMatch()->GetTeamA()->GetPlayers();
    }
    int enemies_in_my_area = 0;
    for(int i = 0; i < enemies.size(); i++)
    {
        Player* enemy = enemies[i];
        if(this->rectangle->IsInside(enemy->GetLocation()))
        {
            enemies_in_my_area++;
        }
    }
    if(enemies_in_my_area > 2)//TODO: MAGIC NUMBER
    {
        player->Kick();//TODO: poner la patada mas fuerte en direccion al arco rival
    }*/
}
