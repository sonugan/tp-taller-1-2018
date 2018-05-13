#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include "../../shared/configuration/configuration.h"
#include "../../shared/model/match.h"

using namespace std;

class GameState
{
    public:
        GameState(Configuration* initial_configuration);
        virtual ~GameState();

    protected:

    private:
        /* Attributes */
        Match* match;

        /* Methods */
        void CreateModel(Configuration* initial_configuration);

};

#endif // GAMESTATE_H
