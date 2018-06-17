#ifndef CHANGEFORMATIONREQUEST_H
#define CHANGEFORMATIONREQUEST_H

#include "../iserializable.h"
#include <string>
#include <vector>
#include <iostream>

class ChangeFormationRequest : public ISerializable
{
    public:
        ChangeFormationRequest();
        ~ChangeFormationRequest();
        string Serialize();
        void Deserialize(string str_obj);
        string GetFormation();
        void SetFormation(string formation);
        string ToString();
        MESSAGE_TYPE GetMessageType();
    private:
        string formation;
        MESSAGE_TYPE message_type;

};

#endif // CHANGEFORMATIONREQUEST_H
