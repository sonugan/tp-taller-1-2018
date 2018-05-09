#ifndef CLIENT_H
#define CLIENT_H

#include "../shared/configuration/configuration.h"


class Client
{
    public:
        Client(Configuration * configuration);
        virtual ~Client();
        void Init();

    protected:

    private:
        Configuration* config;
};

#endif // CLIENT_H
