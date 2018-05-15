#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <string>
#include "message-type.h"

using namespace std;

class ISerializable
{
    public:
        /* Abstract methods should be declare equal to zero */
        virtual string Serialize() = 0;
        virtual void Deserialize(string str_obj) = 0;
        virtual MESSAGE_TYPE GetMessageType() = 0;
    protected:
    private:
};

#endif // ISERIALIZABLE_H
