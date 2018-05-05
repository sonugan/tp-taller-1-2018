#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H

#include <string>
#include <sstream>
#include <stdarg.h>

using namespace std;

class StringBuilder
{
    public:
        StringBuilder();
        void Append(string str);
        string Build();
        virtual ~StringBuilder();
        ///
        //Concatena una lista de strings, siendo obligatorio que el último sea null
        //EJ: string var = "var";
        //  Concat("foo1", "foo2", var.c_str(), NULL) --> foo1foo2var
        ///
        string Concat(const char* arg, ...);
    protected:
    private:
        string current_string;
};

#endif // STRINGBUILDER_H
