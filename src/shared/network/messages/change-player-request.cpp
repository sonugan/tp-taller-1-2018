#include "change-player-request.h"
#include "../../logger.h"


ChangePlayerRequest::ChangePlayerRequest()
{
    this->message_type = MESSAGE_TYPE::SELECT_REQUEST;
}

ChangePlayerRequest::~ChangePlayerRequest()
{
    //dtor
}

string ChangePlayerRequest::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    return msg_type;
}

void ChangePlayerRequest::Deserialize(string str_obj)
{
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(str_obj));
}

MESSAGE_TYPE ChangePlayerRequest::GetMessageType()
{
    return this->message_type;
}
