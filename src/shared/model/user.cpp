#include "user.h"

User::User(string username, int selected_team)
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

int User::GetSelectedTeam()
{
    return this->selected_team;
}
