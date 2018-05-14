#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <map>
#include "../../shared/configuration/configuration.h"
#include "../../shared/model/match.h"
#include "../../shared/model/user.h"

using namespace std;

class GameState
{
    public:
        GameState(Configuration* initial_configuration);
        virtual ~GameState();

        void AddUser(User* user);

    protected:

    private:
        /* Attributes */
        Match* match;
        map<string, User*> active_users;

        /* Methods */
        void CreateModel(Configuration* initial_configuration);

};

#endif // GAMESTATE_H
