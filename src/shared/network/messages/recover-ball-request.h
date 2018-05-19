#ifndef RECOVERBALLREQUEST_H
#define RECOVERBALLREQUEST_H

#include "../iserializable.h"
#include <string>

class RecoverBallRequest : public ISerializable
{
    public:
        RecoverBallRequest();
        virtual ~RecoverBallRequest();
        string Serialize();
        void Deserialize(string str_obj);
        MESSAGE_TYPE GetMessageType();
    protected:

    private:
        MESSAGE_TYPE message_type;
};

#endif // RECOVERBALLREQUEST_H
