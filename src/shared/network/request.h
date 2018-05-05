#ifndef REQUEST_H
#define REQUEST_H

#include <string.h>

#include "iserializable.h"

using namespace std;

class Request
{
    public:
        Request(string data);
        Request(ISerializable* serializable);
        char* GetData();
        int GetDataSize();
        virtual ~Request();
    protected:
    private:
        char* data;
        int size;
};

#endif // REQUEST_H
