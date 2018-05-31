#ifndef CHANGEPLAYERREQUEST_H
#define CHANGEPLAYERREQUEST_H


#include "../iserializable.h"
#include <string>


class ChangePlayerRequest : public ISerializable
{
    public:
        ChangePlayerRequest();
        virtual ~ChangePlayerRequest();
        string Serialize();
        void Deserialize(string str_obj);
        MESSAGE_TYPE GetMessageType();
    protected:

    private:
        MESSAGE_TYPE message_type;
};

#endif // CHANGEPLAYERREQUEST_H
