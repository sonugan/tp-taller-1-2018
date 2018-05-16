#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "../client.h"

class AbstractController
{
    public:
        AbstractController() {}
        virtual ~AbstractController() {}
        virtual void Handle(const Uint8* keyboard_state_array) = 0;

    protected:
        Client* client;
    private:

};

#endif // ABSTRACTCONTROLLER_H
