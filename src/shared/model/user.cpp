#include "user.h"

User::User(string username, int selected_team)
{
    this->username = username;
    this->selected_team = selected_team;
    this->user_color = USER_COLOR::BLUE; // VER QUE SELECCIONE UNO DISTINTO PARA CADA UNO
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

USER_COLOR User::GetColor()
{
    return this->user_color;
}
