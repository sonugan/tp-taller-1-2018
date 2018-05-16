#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../game.h"
#include "abstract-controller.h"

class Game; // forward declaration
class GameController : public AbstractController
{
    public:
        GameController(Game* game, Client* client);
        virtual ~GameController();
        void Handle(const Uint8* keyboard_state_array);

    protected:

    private:
        void ExitGame(const Uint8 *keyboard_state_array);
        Game* game;
};

#endif // GAMECONTROLLER_H
