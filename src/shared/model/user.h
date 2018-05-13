#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

enum class USER_COLOR {NO_COLOR, RED, BLUE, GREEN, YELLOW};

class User
{
    public:
        User(string username, int selected_team);
        virtual ~User();

        string GetUsername();
        int GetSelectedTeam();
        USER_COLOR GetColor();

    protected:

    private:
        string username;
        int selected_team;
        USER_COLOR user_color;
};

#endif // USER_H
