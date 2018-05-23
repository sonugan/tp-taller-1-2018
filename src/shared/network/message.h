#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstring>

#include "iserializable.h"
#include "message-type.h"

using namespace std;

class Message
{
    public:
//        Message(char* data, int size);
        Message(const string& data);
        Message(ISerializable* serializable);
        const char* GetData();
        int GetDataSize();
        ISerializable* GetDeserializedData(ISerializable* serializable);
        MESSAGE_TYPE GetType();
        virtual ~Message();
    protected:
    private:
        string data;
        MESSAGE_TYPE type;

        /* Methods */
        MESSAGE_TYPE ResolveType(string serialized_data);
};

#endif // MESSAGE_H
