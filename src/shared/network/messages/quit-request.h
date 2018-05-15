#ifndef QUITREQUEST_H
#define QUITREQUEST_H

#include "../iserializable.h"

class QuitRequest : public ISerializable
{
    public:
        QuitRequest();
        virtual ~QuitRequest();

        string Serialize();
        void Deserialize(string str_obj);

    protected:
        MESSAGE_TYPE GetMessageType();
    private:
        MESSAGE_TYPE message_type = MESSAGE_TYPE::LOGIN_REQUEST;
        std::string message;
};

#endif // QUITREQUEST_H
