#include<stdlib.h>

#include "message.h"


/* Este constructor lo usamos en el receive del server o client */
Message::Message(const string& data)
{
    this->data = data;
    this->type = ResolveType(data);
}

/* Este constructor se usa para enviar datos */
Message::Message(ISerializable* serializable)
{
    this->data = serializable->Serialize();
    this->type = serializable->GetMessageType();
}

const char* Message::GetData()
{
    return data.c_str();
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

MESSAGE_TYPE Message::GetType()
{
    return this->type;
}

Message::~Message()
{
}

MESSAGE_TYPE Message::ResolveType(string serialized_data)
{
    /* Magia oscura para convertir el char a un message_type */
    int type = (int) serialized_data.at(0) - 48;
    return static_cast<MESSAGE_TYPE>(type);
}
