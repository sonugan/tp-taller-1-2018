#ifndef USER_H
#define USER_H

#include <string>
#include "user-color.h"
#include "player.h"
#include "team-number.h"

using namespace std;

class Player;
class User
{
    public:
        User(string username, string password, TEAM_NUMBER selected_team, USER_COLOR color);
        virtual ~User();

        string GetUsername();
        string GetPassword();
        TEAM_NUMBER GetSelectedTeam();
        Player* GetSelectedPlayer();
        void SetSelectedPlayer(Player* player);
        USER_COLOR GetUserColor();

    protected:

    private:
        string username;
        string password;
        TEAM_NUMBER selected_team;
        Player* selected_player;
        USER_COLOR user_color;
};

#endif // USER_H
