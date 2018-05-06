#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <sstream>
#include <stdarg.h>
#include <vector>

using namespace std;

class StringUtils
{
    public:
        StringUtils();
        virtual ~StringUtils();
        ///
        //Concatena una lista de strings, siendo obligatorio que el último sea null
        //EJ: string var = "var";
        //  Concat("foo1", "foo2", var.c_str(), NULL) --> foo1foo2var
        ///
        //static string Concat(const char* arg, ...);

        ///
        //Retorna una lista de strings, particionando el string s por el caracter c
        ///
        static const vector<string> Split(const string& s, const char& c);
    protected:
    private:
};

#endif // STRINGUTILS_H
