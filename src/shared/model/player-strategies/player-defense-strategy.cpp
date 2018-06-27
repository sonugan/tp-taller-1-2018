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
        bool my_keeper_has_ball = ball->IsHeldByAnyKeeper() && ball->GetKeeper() == this->player->GetTeam()->GetKeeper();
        int x_ball = ball->GetLocation()->GetX();
        if((ball_team == nullptr || ball_team != this->player->GetTeam()) && !my_keeper_has_ball)
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
            else if(x_ball > 900 && x_ball < 1020)
            {
                vector<Player*> buddies = this->player->GetTeam()->GetPlayers();
                float min_distance = this->player->GetLocation()->Distance(ball->GetLocation());
                Player* nearest_player = this->player;
                for(int i = 0; i < buddies.size(); i++)
                {
                    Player* buddy = buddies[i];
                    float distance = buddy->GetLocation()->Distance(ball->GetLocation());
                    if(buddy != this->player && distance < min_distance)
                    {
                        min_distance = distance;
                        nearest_player = buddy;
                    }
                }
                if(nearest_player == this->player)
                {
                    player->GoTo(ball->GetLocation(), false);
                }
            }
            else
            {
                player->GoBackToDefaultPosition();
            }
        }
        if(player->HasBall() || my_keeper_has_ball)
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
