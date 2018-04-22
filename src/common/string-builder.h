#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H

#include <string>
#include <sstream>

using namespace std;

class StringBuilder
{
    public:
        StringBuilder();
        void Append(string str);
        string Build();
        virtual ~StringBuilder();
    protected:
    private:
        string current_string;
};

#endif // STRINGBUILDER_H
