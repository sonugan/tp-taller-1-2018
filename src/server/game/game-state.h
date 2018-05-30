#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <map>
#include "../../shared/configuration/configuration.h"
#include "../../shared/model/match.h"
#include "../../shared/model/user.h"
#include "../../shared/model/player.h"

using namespace std;

class GameState
{
    public:
        GameState(Configuration* initial_configuration);
        virtual ~GameState();

        Match* GetMatch();
        void AddUser(string username, string password);
        bool WasConnected(User* user);

        protected:

    private:
        /* Attributes */
        Match* match;
        map<string, string> users = {};

        /* Methods */
        void CreateModel(Configuration* initial_configuration);

};

#endif // GAMESTATE_H
