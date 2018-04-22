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
