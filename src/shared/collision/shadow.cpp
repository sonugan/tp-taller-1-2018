#include "shadow.h"

Shadow::Shadow(Player* player)
{
    this->player = player;
    this->circle = new Circle(HALO_RADIUS, new Location(this->player->GetLocation()));
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
    for(u_int i = 0; can && i< players_a.size(); i++)
    {
        if(players_a[i] != this->player && this->circle->ExistsCollision2d(players_a[i]->GetShadow()->circle))
        {
            can = false;
        }
    }

    vector<Player*> players_b = this->player->GetTeam()->GetMatch()->GetTeamB()->GetPlayers();
    for(u_int i = 0; can && i< players_b.size(); i++)
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

Location* Shadow::GetBestNextPosition(Location* target, int speed)
{
    if(CanMoveTo(target))
    {
        return target;
    }
    Location* player_location = this->player->GetLocation();
    int x = player_location->GetX();
    int y = player_location->GetY();
    int z = player_location->GetZ();

    Location* best_location = nullptr;
    float best_distance = 1000000;

    Location* north = new Location(x, y - speed, z);
    u_int north_distance = north->ManhattanDistance(target);
    IsBetterAlternative(north, north_distance, best_location, &best_distance);
    delete north;

    Location* south = new Location(x, y + speed, z);
    u_int south_distance = south->ManhattanDistance(target);
    IsBetterAlternative(south, south_distance, best_location, &best_distance);
    delete south;

    Location* east = new Location(x + speed, y, z);
    u_int east_distance = east->ManhattanDistance(target);
    IsBetterAlternative(east, east_distance, best_location, &best_distance);
    delete east;

    Location* west = new Location(x - speed, y, z);
    u_int west_distance = west->ManhattanDistance(target);
    IsBetterAlternative(west, west_distance, best_location, &best_distance);
    delete west;

    Location* northeast = new Location(x + speed, y - speed, z);
    u_int northeast_distance = northeast->ManhattanDistance(target);
    IsBetterAlternative(northeast, northeast_distance, best_location, &best_distance);
    delete northeast;

    Location* southeast = new Location(x + speed, y + speed, z);
    u_int southeast_distance = southeast->ManhattanDistance(target);
    IsBetterAlternative(southeast, southeast_distance, best_location, &best_distance);
    delete southeast;

    Location* northwest = new Location(x - speed, y - speed, z);
    u_int northwest_distance = northwest->ManhattanDistance(target);
    IsBetterAlternative(northwest, northwest_distance, best_location, &best_distance);
    delete northwest;

    Location* southwest = new Location(x - speed, y + speed, z);
    u_int southwest_distance = southwest->ManhattanDistance(target);
    IsBetterAlternative(southwest, southwest_distance, best_location, &best_distance);
    delete southwest;

    if(best_location != nullptr)
    {
        return new Location(best_location);
    }
    else
    {
        return new Location(this->player->GetLocation());//Si no se puede mover hacia ningun lado
    }
}

void Shadow::IsBetterAlternative(Location* possible_location, float distance_to_target, Location* best_location, float* best_distance)
{
    if(CanMoveTo(possible_location))
    {
        if(*best_distance > distance_to_target)
        {
            best_location = new Location(possible_location);
            *best_distance = distance_to_target;
        }
    }
}
