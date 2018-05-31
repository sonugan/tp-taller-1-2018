#ifndef PASSBALLREQUEST_H
#define PASSBALLREQUEST_H

#include "../iserializable.h"
#include <string>


class PassBallRequest : public ISerializable
{
    public:
        PassBallRequest();
        virtual ~PassBallRequest();
        string Serialize();
        void Deserialize(string str_obj);
        MESSAGE_TYPE GetMessageType();
    protected:

    private:
        MESSAGE_TYPE message_type;
};
#endif // PASSBALLREQUEST_H
