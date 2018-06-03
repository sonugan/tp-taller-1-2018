#include "shadow.h"

Shadow::Shadow(Player* player)
{
    this->player = player;
    this->circle = new Circle(10, new Location(this->player->GetLocation()));//TODO: magic number
}

Shadow::~Shadow()
{
    delete this->circle;
}

bool Shadow::CollidesWith(Shadow* other_shadow)
{
    return this->circle->ExistsCollision2d(other_shadow->circle);
}

void Shadow::PlayerHasChanged()
{
    this->circle->Move(this->player->GetLocation());
}

bool Shadow::CanMoveTo(Location* location)
{
    Location* current_location = new Location(this->circle->GetCenter());
    this->circle->Move(location);

    bool can = true;
    vector<Player*> players_a = this->player->GetTeam()->GetMatch()->GetTeamA()->GetPlayers();
    for(int i = 0; can && i< players_a.size(); i++)
    {
        if(players_a[i] != this->player && this->circle->ExistsCollision2d(players_a[i]->GetShadow()->circle))
        {
            can = false;
        }
    }

    vector<Player*> players_b = this->player->GetTeam()->GetMatch()->GetTeamB()->GetPlayers();
    for(int i = 0; can && i< players_b.size(); i++)
    {
        if(players_b[i] != this->player && this->circle->ExistsCollision2d(players_b[i]->GetShadow()->circle))
        {
            can = false;
        }
    }
    this->circle->Move(current_location);
    delete current_location;
    return can;
}
