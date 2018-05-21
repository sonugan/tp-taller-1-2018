#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <map>
#include <string>
#include <stack>
#include "../../shared/network/messages/login-request.h"
#include "../../shared/model/user.h"
#include "../../shared/network/client-socket.h"
#include "../../shared/model/team-number.h"

using namespace std;

class SessionManager
{
    public:
        SessionManager(map<string, string> credentials, int max_allowed_users);
        virtual ~SessionManager();

        User* Authenticate(ClientSocket* client, LoginRequest* login_request);
        void RemoveSession(string username);

        map<string, User*> GetAuthenticatedUsers();
        int GetAutheticatedUsersCount();

        User* GetUserBySocketID(int socket_id);
        bool IsReadyToStart();

    protected:

    private:
        /* Attributes */
        map<string, string> credentials = {};
        map<string, User*> authenticated_users = {};
        map<int, User*> clientsocket_user_association = {};
        int max_allowed_users;

        stack<USER_COLOR> colors;

        /* Methods */
        bool IsValidUser(string username, string password);
        bool IsAuthenticated(LoginRequest* login_request);

        USER_COLOR GetColorToAssign();
        TEAM_NUMBER ParseSelectedTeam(string selected_team);
};

#endif // SESSIONMANAGER_H
