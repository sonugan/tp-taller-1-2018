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
            StringBuilder b;
            return b.Concat(this->username.c_str(), "|", this->password.c_str());
        }
        void Deserialize(string str_obj)
        {
            std::vector<std::string> data = StringUtils::Split(str_obj, '|');
            this->username = data[0];
            this->password = data[1];
            this->team = data[2];
            this->server_ip = data[3];
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
    private:
        string username;
        string password;
        string team;
        string server_ip;

};

#endif //LOGIN_H
