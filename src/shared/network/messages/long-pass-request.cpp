#include "long-pass-request.h"
#include "../../logger.h"
#include "../../utils/string-utils.h"

LongPassRequest::LongPassRequest(unsigned int power)
{
    this->message_type = MESSAGE_TYPE::LONG_PASS_REQUEST;
    this->power = power;
}

LongPassRequest::LongPassRequest(){}

LongPassRequest::~LongPassRequest()
{
    //dtor
}

string LongPassRequest::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    Logger::getInstance()->info(msg_type);
    string msg = msg_type + "|" + to_string((u_int)this->power);
    return msg;
}

void LongPassRequest::Deserialize(string str_obj)
{
    std::vector<std::string> data = StringUtils::Split(str_obj, '|');
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(data[0]));
    this->power = stoi(data[1]);
}

MESSAGE_TYPE LongPassRequest::GetMessageType()
{
    return this->message_type;
}

unsigned int LongPassRequest::GetPower()
{
    return this->power;
}
