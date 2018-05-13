#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
    public:
        User(string username, int selected_team);
        virtual ~User();

        string GetUsername();
        int GetSelectedTeam();

    protected:

    private:
        string username;
        int selected_team;
};

#endif // USER_H
