#ifndef QUITREQUEST_H
#define QUITREQUEST_H

#include "../iserializable.h"

class QuitRequest : public ISerializable
{
    public:
        QuitRequest(string username);
        virtual ~QuitRequest();

        string Serialize();
        void Deserialize(string str_obj);

    protected:
        MESSAGE_TYPE GetMessageType();
    private:
        MESSAGE_TYPE message_type = MESSAGE_TYPE::LOGIN_REQUEST;
        std::string username;
};

#endif // QUITREQUEST_H
