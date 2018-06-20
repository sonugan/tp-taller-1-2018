#include "recover-ball-request.h"
#include "../../logger.h"

RecoverBallRequest::RecoverBallRequest()
{
    this->message_type = MESSAGE_TYPE::RECOVER_REQUEST;
}

RecoverBallRequest::~RecoverBallRequest()
{
    //dtor
}

string RecoverBallRequest::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    return msg_type;
}

void RecoverBallRequest::Deserialize(string str_obj)
{
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(str_obj));
}

MESSAGE_TYPE RecoverBallRequest::GetMessageType()
{
    return this->message_type;
}
