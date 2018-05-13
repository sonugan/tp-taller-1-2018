#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <string>

using namespace std;

class ISerializable
{
    public:
        virtual string Serialize(){};
        virtual void Deserialize(string str_obj){};
    protected:
    private:
};

#endif // ISERIALIZABLE_H
