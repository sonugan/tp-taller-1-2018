#ifndef ISERIALIZER_H
#define ISERIALIZER_H

#include <string>

using namespace std;

template <class T>
class ISerializer
{
    public:
        virtual string Serialize(T obj);
        virtual T Deserialize(string str_obj);
    protected:
    private:
};

#endif // ISERIALIZER_H
