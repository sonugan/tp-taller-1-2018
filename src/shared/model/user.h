#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
    public:
        User(string username, string selected_team);
        virtual ~User();

        string GetUsername();
        string GetSelectedTeam();

    protected:

    private:
        string username;
        string selected_team;
};

#endif // USER_H
