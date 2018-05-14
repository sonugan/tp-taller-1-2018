#include "user.h"

User::User(string username, string password, int selected_team)
{
    this->username= username;
    this->password = password;
    this->selected_team= selected_team;
    this->user_color = USER_COLOR::BLUE;
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

string User::GetPassword()
{
    return this->password;
}

USER_COLOR User::GetUserColor()
{
    return this->user_color;
}
