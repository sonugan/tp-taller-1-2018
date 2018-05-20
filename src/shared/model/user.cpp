#include "user.h"

User::User(string username, string password, TEAM_NUMBER selected_team, USER_COLOR color)
{
    this->username= username;
    this->password = password;
    this->selected_team= selected_team;
    this->user_color = color;
}

User::~User()
{
    //dtor
}

string User::GetUsername()
{
    return this->username;
}

TEAM_NUMBER User::GetSelectedTeam()
{
    return this->selected_team;
}

string User::GetPassword()
{
    return this->password;
}

USER_COLOR User::GetUserColor()
{
    return this->user_color;
}

Player* User::GetSelectedPlayer()
{
    return this->selected_player;
}

void User::SetSelectedPlayer(Player* player)
{
    this->selected_player = player;
}
