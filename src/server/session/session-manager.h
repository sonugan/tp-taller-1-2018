#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <map>
#include <string>
#include "../../shared/network/login.cpp"
#include "../../shared/model/user.h"

using namespace std;

class SessionManager
{
    public:
        SessionManager(map<string, string> credentials);
        virtual ~SessionManager();

        User* Authenticate(Login* login_request);
        void RemoveSession(string username);

    protected:

    private:
        /* Attributes */
        map<string, string> credentials = {};
        map<string, User*> authenticated_users = {};

        /* Methods */
        bool IsValidUser(string username, string password);
        bool IsAuthenticated(Login* login_request);
};

#endif // SESSIONMANAGER_H
