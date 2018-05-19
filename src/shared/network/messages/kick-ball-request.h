#ifndef KICK-BALL-REQUEST_H
#define KICK-BALL-REQUEST_H

#include "../iserializable.h"
#include <string>

class KickBallRequest : public ISerializable
{
    public:
        KickBallRequest();
        virtual ~KickBallRequest();
        string Serialize();
        void Deserialize(string str_obj);
        MESSAGE_TYPE GetMessageType();
    protected:

    private:
        MESSAGE_TYPE message_type;
};

#endif // KICK-BALL-REQUEST_H
