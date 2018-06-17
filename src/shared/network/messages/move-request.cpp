#include "move-request.h"
#include "../../logger.h"

MoveRequest::MoveRequest(){}

MoveRequest::MoveRequest(DIRECTION direction, bool run)
{
    this->direction = direction;
    this->run = run;
    this->message_type = MESSAGE_TYPE::MOVE_REQUEST;
}

MoveRequest::~MoveRequest()
{
    //dtor
}

string MoveRequest::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    string run = this->run ? "1" : "0";
    string msg = msg_type + "|" + to_string((u_int)this->direction) + "|" + run;
    return msg;
}

void MoveRequest::Deserialize(string str_obj)
{
    std::vector<std::string> data = StringUtils::Split(str_obj, '|');
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(data[0]));
    this->direction = static_cast<DIRECTION>(stoi(data[1]));
    this->run = data[2] == "1";
}

DIRECTION MoveRequest::GetDirection(){
    return this->direction;
}

bool MoveRequest::IsRunning(){
    return this->run;
}

MESSAGE_TYPE MoveRequest::GetMessageType()
{
    return this->message_type;
}

