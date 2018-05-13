#include "user.h"

User::User(string username, string selected_team)
{
    this->username= username;
    this->selected_team= selected_team;
}

User::~User()
{
    //dtor
}

string User::GetUsername()
{
    return this->username;
}

string User::GetSelectedTeam()
{
    return this->selected_team;
}
