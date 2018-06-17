#ifndef KICKBALLREQUEST_H
#define KICKBALLREQUEST_H

#include "../iserializable.h"
#include <string>

class KickBallRequest : public ISerializable
{
    public:
        KickBallRequest();
        KickBallRequest(unsigned int power);
        virtual ~KickBallRequest();
        string Serialize();
        void Deserialize(string str_obj);
        MESSAGE_TYPE GetMessageType();
        unsigned int GetPower();
    protected:

    private:
        MESSAGE_TYPE message_type;
        unsigned int power;
};

#endif // KICKBALLREQUEST_H
