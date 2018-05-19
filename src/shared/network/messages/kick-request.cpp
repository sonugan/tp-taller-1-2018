#include "kick-request.h"

KickResquest::KickResquest()
{
    this->message_type = MESSAGE_TYPE::KICK_REQUEST;
}

KickResquest()::~KickResquest()
{
    //dtor
}

string KickRequest::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    cout << msg_type << endl;
    string msg = msg_type;
    return msg;
}

void KickRequest::Deserialize(string str_obj)
{
    this->message_type = static_cast<MESSAGE_TYPE>(str_obj);
}

MESSAGE_TYPE KickRequest::GetMessageType()
{
    return this->message_type;
}
