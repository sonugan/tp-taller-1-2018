#include "string-builder.h"

StringBuilder::StringBuilder()
{
    this->current_string = "";
}

StringBuilder::~StringBuilder()
{
    //dtor
}

void StringBuilder::Append(string str)
{
    stringstream ss;
    ss << this->current_string << str;
    this->current_string = ss.str();
}

string StringBuilder::Build()
{
    return this->current_string;
}

string StringBuilder::Concat(const char* arg, ...)
{
    va_list args;
    stringstream ss;
    for(va_start(args, arg); arg != NULL; arg = va_arg(args, const char*))
    {
        ss << arg;
    }
    va_end(args);
    return ss.str();
}
