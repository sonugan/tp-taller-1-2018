#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

#include "iserializable.h"

using namespace std;

template <class T>
class Response
{
    public:
        Response(string data);
        Response(ISerializable* serializable);
        char* GetData();
        int GetDataSize();
        virtual ~Response();
    protected:
    private:
        char* data;
        int size;
};

#endif // RESPONSE_H
