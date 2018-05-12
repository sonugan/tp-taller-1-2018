#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstring>

#include "iserializable.h"

using namespace std;

class Message
{
    public:
        Message(char* data, int size);
        Message(string data);
        Message(ISerializable* serializable);
        char* GetData();
        int GetDataSize();
        ISerializable* GetDeserializedData(ISerializable* serializable);
        virtual ~Message();
    protected:
    private:
        string data;
};

#endif // MESSAGE_H
