#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "../iserializable.h"
#include <string>
#include <vector>
#include <iostream>

class LoginRequest : public ISerializable
{
    public:
        LoginRequest();
        ~LoginRequest();
        string Serialize();
        void Deserialize(string str_obj);
        string GetUsername();
        string GetPassword();
        string GetTeam();
        string GetServerIp();
        void SetUsername(string username);
        void SetPassword(string password);
        void SetTeam(string team);
        void SetServerIp(string server_ip);
        string ToString();
        MESSAGE_TYPE GetMessageType();
    private:
        string username;
        string password;
        string team;
        string server_ip;
        MESSAGE_TYPE message_type;

};

#endif // LOGINREQUEST_H
