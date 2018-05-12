#include<stdlib.h>

#include "message.h"

Message::Message(string data)
{
    this->data = data;
}

Message::Message(ISerializable* serializable)
{
    this->data = serializable->Serialize();
}

char* Message::GetData()
{
    return (char*)data.c_str();
}

ISerializable* Message::GetDeserializedData(ISerializable* serializable)
{
    serializable->Deserialize(this->data);
    return serializable;
}

int Message::GetDataSize()
{
    return this->data.length();
}

Message::~Message()
{
}
