#ifndef MOVEREQUEST_H
#define MOVEREQUEST_H

#include "../iserializable.h"
#include <string>


class MoveRequest : public ISerializable
{
    public:
        MoveRequest(DIRECTION direction, bool run);
        virtual ~MoveRequest();
        string Serialize();
        void Deserialize(string str_obj);
        MESSAGE_TYPE GetMessageType();
        DIRECTION GetDirection();
        bool IsRunning();
    protected:

    private:
        MESSAGE_TYPE message_type;
};

#endif // MOVEREQUEST_H
