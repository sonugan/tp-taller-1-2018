#ifndef LONGPASSREQUEST_H
#define LONGPASSREQUEST_H

#include "../iserializable.h"
#include <string>
#include <vector>
#include <iostream>

class LongPassRequest : public ISerializable
{
    public:
        LongPassRequest();
        LongPassRequest(unsigned int power);
        virtual ~LongPassRequest();
        string Serialize();
        void Deserialize(string str_obj);
        MESSAGE_TYPE GetMessageType();
        unsigned int GetPower();

    protected:

    private:
        unsigned int power;
        MESSAGE_TYPE message_type;
};

#endif // LONGPASSREQUEST_H
