#include "health-check.h"
#include "../../logger.h"

HealthCheck::HealthCheck()
{
    this->message_type = MESSAGE_TYPE::HEALTH_CHECK;
}

HealthCheck::~HealthCheck()
{
    //dtor
}

string HealthCheck::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    return msg_type;
}

void HealthCheck::Deserialize(string str_obj)
{
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(str_obj));
}

MESSAGE_TYPE HealthCheck::GetMessageType()
{
    return this->message_type;
}
