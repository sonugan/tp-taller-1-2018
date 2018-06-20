#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <map>
#include "../../shared/configuration/configuration.h"
#include "../../shared/model/match.h"
#include "../../shared/model/user.h"
#include "../../shared/model/player.h"
#include "../../shared/model/timer.h"
#include "../../shared/model/keeper.h"

using namespace std;

class GameState
{
    public:
        GameState(Configuration* initial_configuration);
        virtual ~GameState();

        Match* GetMatch();
        void AddUser(string username, string password);
        bool WasConnected(User* user);
        void UpdateMatchState();
        void Start();

        protected:

    private:
        /* Attributes */
        Match* match = NULL;
        map<string, string> users = {};
        Timer* timer = NULL;

        /* Methods */
        void CreateModel(Configuration* initial_configuration);

};

#endif // GAMESTATE_H
