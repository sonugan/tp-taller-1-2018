#ifndef MOVEREQUEST_H
#define MOVEREQUEST_H

#include "../iserializable.h"
#include <string>


class MoveRequest : public ISerializable
{
    public:
        MoveRequest();
        virtual ~MoveRequest();
        string Serialize();
        void Deserialize(string str_obj);
        MESSAGE_TYPE GetMessageType();
    protected:

    private:
        MESSAGE_TYPE message_type;
};

#endif // MOVEREQUEST_H
