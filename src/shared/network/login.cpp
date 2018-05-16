#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <iostream>
#include <vector>

#include "iserializable.h"

#include "../utils/string-builder.h"
#include "../utils/string-utils.h"

class Login : public ISerializable
{
    public:
        Login(){
            this->username = "";
            this->password = "";
            this->team = "";
            this->server_ip = "";
        }
        ~Login(){};
        string Serialize()
        {
            StringBuilder string_builder;
            string msg_type = to_string(this->GetMessageType());
            cout << msg_type << endl;
            string msg = msg_type + "|" + this->username + "|" + this->password + "|" + this->team;
            return msg;
//            return string_builder.Concat(msg_type.c_str(), "|", this->username.c_str(), "|", this->password.c_str(), "|", this->team.c_str());
        }
        void Deserialize(string str_obj)
        {
            std::vector<std::string> data = StringUtils::Split(str_obj, '|');
            this->message_type = static_cast<MESSAGE_TYPE>(stoi(data[0]));
            this->username = data[1];
            this->password = data[2];
            this->team = data[3];
        }
        string GetUsername() { return this->username; }
        string GetPassword() { return this->password; }
        string GetTeam() { return this->team; }
        string GetServerIp() { return this->server_ip; }
        void SetUsername(string username) { this->username = username; }
        void SetPassword(string password) { this->password = password; }
        void SetTeam(string team) { this->team = team; }
        void SetServerIp(string server_ip) { this->server_ip = server_ip; }
        string ToString() {
            return username + "-" + password + "-" + server_ip + "-" + team;
        }
    protected:
        MESSAGE_TYPE GetMessageType()
        {
            return this->message_type;
        }
    private:
        string username;
        string password;
        string team;
        string server_ip;
        MESSAGE_TYPE message_type = MESSAGE_TYPE::LOGIN_REQUEST;

};

#endif //LOGIN_H
