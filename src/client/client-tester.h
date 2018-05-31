#ifndef CLIENTTESTER_H
#define CLIENTTESTER_H

#include "client.h"
#include "../shared/configuration/configuration.h"

class ClientTester
{
    public:
        ClientTester(Configuration* config);
        virtual ~ClientTester();

        void TestCompleteFlow();

    protected:

    private:
        Client* client;
};

#endif // CLIENTTESTER_H
