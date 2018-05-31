#ifndef HEALTHCHECK_H
#define HEALTHCHECK_H

#include "../iserializable.h"
#include <string>


class HealthCheck : public ISerializable
{
    public:
        HealthCheck();
        virtual ~HealthCheck();
        string Serialize();
        void Deserialize(string str_obj);
        MESSAGE_TYPE GetMessageType();
    protected:

    private:
        MESSAGE_TYPE message_type;
};
#endif // HEALTHCHECK_H
