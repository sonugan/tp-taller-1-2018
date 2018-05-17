#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <map>
#include <string>
#include "../../shared/network/messages/login-request.h"
#include "../../shared/model/user.h"
#include "../../shared/network/client-socket.h"

using namespace std;

class SessionManager
{
    public:
        SessionManager(map<string, string> credentials);
        virtual ~SessionManager();

        User* Authenticate(ClientSocket* client, LoginRequest* login_request);
        void RemoveSession(string username);

    protected:

    private:
        /* Attributes */
        map<string, string> credentials = {};
        map<string, User*> authenticated_users = {};
        map<int, User*> clientsocket_user_association = {};

        /* Methods */
        bool IsValidUser(string username, string password);
        bool IsAuthenticated(LoginRequest* login_request);
};

#endif // SESSIONMANAGER_H
