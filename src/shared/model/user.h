#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

enum class USER_COLOR {NO_COLOR, RED, BLUE, GREEN, YELLOW};

class User
{
    public:
        User(string username, string password, int selected_team);
        virtual ~User();

        string GetUsername();
        string GetPassword();
        int GetSelectedTeam();
        USER_COLOR GetUserColor();

    protected:

    private:
        string username;
        string password;
        int selected_team;
        USER_COLOR user_color;
};

#endif // USER_H
