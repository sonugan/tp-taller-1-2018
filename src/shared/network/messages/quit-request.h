#ifndef QUITREQUEST_H
#define QUITREQUEST_H

#include "../iserializable.h"

class QuitRequest : public ISerializable
{
    public:
        QuitRequest();
        virtual ~QuitRequest();

        string Serialize();

    protected:

    private:
};

#endif // QUITREQUEST_H
