#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

enum class USER_COLOR {NO_COLOR = 1, RED = 2, BLUE = 3, GREEN = 4, YELLOW = 5};

class Player;

class User
{
    public:
        User(string username, string password, int selected_team, USER_COLOR color);
        virtual ~User();

        string GetUsername();
        string GetPassword();
        int GetSelectedTeam();
        Player* GetSelectedPlayer();
        void SetSelectedPlayer(Player* player);
        USER_COLOR GetUserColor();

    protected:

    private:
        string username;
        string password;
        int selected_team;
        Player* selected_player;
        USER_COLOR user_color;
};

#endif // USER_H
