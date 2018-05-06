#ifndef LOGIN_H
#define LOGIN_H

#include <string.h>
#include <iostream>
#include <vector>

#include "iserializable.h"

#include "../utils/string-builder.h"
#include "../utils/string-utils.h"

class Login : public ISerializable
{
    public:
        Login()
        {

        }
        Login(string Username, string Password)
        {
            this->Username = Username;
            this->Password = Password;
        }
        string Serialize()
        {
            StringBuilder b;
            return b.Concat(this->Username.c_str(), "|", this->Password.c_str());
        }
        void Deserialize(string str_obj)
        {
            std::vector<std::string> data = StringUtils::Split(str_obj, '|');
            this->Username = data[0];
            this->Password = data[1];
        }
        string GetUsername() { return this->Username; }
    private:
        string Username;
        string Password;

};

#endif //LOGIN_H
