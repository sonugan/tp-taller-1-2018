#include "kick-ball-request.h"
#include "../../logger.h"
#include "../../utils/string-utils.h"

KickBallRequest::KickBallRequest(){}

KickBallRequest::KickBallRequest(unsigned int power)
{
    this->message_type = MESSAGE_TYPE::KICK_REQUEST;
    this->power = power;
}

KickBallRequest::~KickBallRequest()
{
    //dtor
}

string KickBallRequest::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    Logger::getInstance()->info(msg_type);
    string msg = msg_type + "|" + to_string((u_int)this->power);
    return msg;
}

void KickBallRequest::Deserialize(string str_obj)
{
    std::vector<std::string> data = StringUtils::Split(str_obj, '|');
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(data[0]));
    this->power = stoi(data[1]);
}

MESSAGE_TYPE KickBallRequest::GetMessageType()
{
    return this->message_type;
}

unsigned int KickBallRequest::GetPower()
{
    return this->power;
}
