#include "response.h"

template <typename T>
Response<T>::Response(string data)
{
    this->data = (char*)data.c_str();
    this->size = strlen(this->data);
}

template <typename T>
Response<T>::Response(ISerializable* serializable)
{
    string serialized = serializable->Serialize();
    this->data = (char*)serialized.c_str();
    this->size = strlen(this->data);
}

template <typename T>
char* Response<T>::GetData()
{
    return this->data;
}

template <typename T>
int Response<T>::GetDataSize()
{
    return this->size;
}

template <typename T>
Response<T>::~Response()
{

}
