#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "../client.h"
#include "../sound/sound-manager.h"

class AbstractController
{
    public:
        AbstractController() { this->sound_manager = new SoundManager(); }
        virtual ~AbstractController() { delete this->sound_manager; }
        virtual void Handle(const Uint8* keyboard_state_array) = 0;

    protected:
        Client* client;
        SoundManager* sound_manager;
    private:

};

#endif // ABSTRACTCONTROLLER_H
