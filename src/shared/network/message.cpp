#include<stdlib.h>

#include "message.h"

Message::Message(char* data, int size)
{
    this->data = data;
    this->size = size;
}

Message::Message(string data)
{
    this->data = (char*)data.c_str();
    this->size = strlen(this->data);
}

Message::Message(ISerializable* serializable)
{
    string serialized = serializable->Serialize();
    this->data = (char*)serialized.c_str();
    this->size = strlen(this->data);
}

char* Message::GetData()
{
    return this->data;
}

ISerializable* Message::GetDeserializedData(ISerializable* serializable)
{
    serializable->Deserialize(string(this->data));
    return serializable;
}

int Message::GetDataSize()
{
    return this->size;
}

Message::~Message()
{
}
