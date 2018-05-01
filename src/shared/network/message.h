#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

#include "iserializer.h"

using namespace std;

class Message
{
    public:
        Message(char* data, int size);
        char* GetData();
        int GetDataSize();
        virtual ~Message();
    protected:
    private:
        char* data;
        int size;
};

#endif // MESSAGE_H
