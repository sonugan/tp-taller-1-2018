#include "change-formation-request.h"
#include "../../utils/string-utils.h"

ChangeFormationRequest::ChangeFormationRequest(){
    this->message_type = MESSAGE_TYPE::CHANGE_FORMATION_REQUEST;
    this->formation = "";
}
ChangeFormationRequest::~ChangeFormationRequest(){};

string ChangeFormationRequest::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    string msg = msg_type + "|" + this->formation;
    return msg;
}

void ChangeFormationRequest::Deserialize(string str_obj)
{
    std::vector<std::string> data = StringUtils::Split(str_obj, '|');
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(data[0]));
    this->formation = data[1];
}

string ChangeFormationRequest::GetFormation() { return this->formation; }
void ChangeFormationRequest::SetFormation(string formation) { this->formation = formation; }
string ChangeFormationRequest::ToString() {
    return this->formation;
}

MESSAGE_TYPE ChangeFormationRequest::GetMessageType()
{
    return this->message_type;
}
