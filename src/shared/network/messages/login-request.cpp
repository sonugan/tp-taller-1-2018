#include "login-request.h"
#include "../../utils/string-utils.h"

LoginRequest::LoginRequest(){
    this->message_type = MESSAGE_TYPE::LOGIN_REQUEST;
    this->username = "";
    this->password = "";
    this->team = "";
    this->server_ip = "";
}
LoginRequest::~LoginRequest(){};

string LoginRequest::Serialize()
{
    string msg_type = to_string(this->GetMessageType());
    cout << msg_type << endl;
    string msg = msg_type + "|" + this->username + "|" + this->password + "|" + this->team;
    return msg;
//            return string_builder.Concat(msg_type.c_str(), "|", this->username.c_str(), "|", this->password.c_str(), "|", this->team.c_str());
}
void LoginRequest::Deserialize(string str_obj)
{
    std::vector<std::string> data = StringUtils::Split(str_obj, '|');
    this->message_type = static_cast<MESSAGE_TYPE>(stoi(data[0]));
    this->username = data[1];
    this->password = data[2];
    this->team = data[3];
}
string LoginRequest::GetUsername() { return this->username; }
string LoginRequest::GetPassword() { return this->password; }
string LoginRequest::GetTeam() { return this->team; }
string LoginRequest::GetServerIp() { return this->server_ip; }
void LoginRequest::SetUsername(string username) { this->username = username; }
void LoginRequest::SetPassword(string password) { this->password = password; }
void LoginRequest::SetTeam(string team) { this->team = team; }
void LoginRequest::SetServerIp(string server_ip) { this->server_ip = server_ip; }
string LoginRequest::ToString() {
    return username + "-" + password + "-" + server_ip + "-" + team;
}

MESSAGE_TYPE LoginRequest::GetMessageType()
{
    return this->message_type;
}
