#include "move-request.h"
#include "../../logger.h"

MoveRequest::MoveRequest()
{
    this->message_type = MESSAGE_TYPE::MOVE_REQUEST;
}

MoveRequest::~MoveRequest()
{
    //dtor
}

string MoveRequest::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    Logger::getInstance()->info(msg_type);
    return msg_type;
}

void MoveRequest::Deserialize(string str_obj)
{
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(str_obj));
}

MESSAGE_TYPE MoveRequest::GetMessageType()
{
    return this->message_type;
}

