#include "quit-request.h"

#include <string>
#include <vector>
#include "../../utils/string-utils.h"


QuitRequest::QuitRequest(std::string username)
{
    this->username = username;
}

QuitRequest::~QuitRequest()
{
    //dtor
}

std::string QuitRequest::Serialize()
{
    std::string msg_type = to_string(this->GetMessageType());
    std::string msg = msg_type + "|" + username;
    return msg;
}

void QuitRequest::Deserialize(std::string str_obj)
{
    std::vector<std::string> data = StringUtils::Split(str_obj, '|');
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(data[0]));
    this->username = data[1];
}

MESSAGE_TYPE QuitRequest::GetMessageType()
{
    return this->message_type;
}

std::string QuitRequest::GetUsername()
{
    return this->username;
}
