#include "string-utils.h"

StringUtils::StringUtils()
{
}

StringUtils::~StringUtils()
{
}

const vector<string> StringUtils::Split(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

bool StringUtils::IsInteger(const string str)
{
    return !str.empty() && find_if(str.begin(),str.end(),
        [](char c){ return !isdigit(c); }) == str.end();
}
