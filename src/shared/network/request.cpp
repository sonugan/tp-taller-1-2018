#include "request.h"

#include <iostream>

Request::Request(string data)
{
    cout << data << endl;
    this->data = (char*)data.c_str();
    this->size = strlen(this->data);
}

Request::Request(ISerializable* serializable)
{
    string serialized = serializable->Serialize();
    this->data = (char*)serialized.c_str();
    this->size = strlen(this->data);
}

char* Request::GetData()
{
    return this->data;
}

int Request::GetDataSize()
{
    return this->size;
}

Request::~Request()
{
}
