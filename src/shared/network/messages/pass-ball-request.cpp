#include "pass-ball-request.h"
#include "../../logger.h"

PassBallRequest::PassBallRequest()
{
    this->message_type = MESSAGE_TYPE::PASS_REQUEST;
}

PassBallRequest::~PassBallRequest()
{
    //dtor
}

string PassBallRequest::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    return msg_type;
}

void PassBallRequest::Deserialize(string str_obj)
{
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(str_obj));
}

MESSAGE_TYPE PassBallRequest::GetMessageType()
{
    return this->message_type;
}
