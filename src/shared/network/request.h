#ifndef REQUEST_H
#define REQUEST_H

#include <string.h>
#include <iostream>

#include "iserializable.h"

using namespace std;

class Request
{
    public:
        Request(string data);
        Request(ISerializable* serializable);//TODO: no está funcionando cuando recibe la info
        char* GetData();
        int GetDataSize();
        virtual ~Request();
    protected:
    private:
        char* data;
        int size;
};

#endif // REQUEST_H
