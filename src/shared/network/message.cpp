#include<stdlib.h>

#include "message.h"

Message::Message(char* data, int size)
{
    this->data = data;
    this->size = size;
}

char* Message::GetData()
{
    return this->data;
}

int Message::GetDataSize()
{
    return this->size;
}

Message::~Message()
{
}
