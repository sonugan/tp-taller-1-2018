#include "kick-ball-request.h"
#include "../../logger.h"


KickBallRequest::KickBallRequest()
{
    this->message_type = MESSAGE_TYPE::KICK_REQUEST;
}

KickBallRequest::~KickBallRequest()
{
    //dtor
}

string KickBallRequest::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    return msg_type;
}

void KickBallRequest::Deserialize(string str_obj)
{
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(str_obj));
}

MESSAGE_TYPE KickBallRequest::GetMessageType()
{
    return this->message_type;
}
