#ifndef KICK-REQUEST_H
#define KICK-REQUEST_H

#include "../iserializable.h"


class KickResquest : public ISerializable
{
    public:
        KickResquest();
        virtual ~KickResquest();
        string Serialize();
        void Deserialize(string str_obj);
        MESSAGE_TYPE GetMessageType();
    protected:

    private:
};

#endif // KICK-REQUEST_H
