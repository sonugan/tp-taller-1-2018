#include "quit-request.h"

#include <string>

using namespace std;

QuitRequest::QuitRequest()
{
    //ctor
}

QuitRequest::~QuitRequest()
{
    //dtor
}

string QuitRequest::Serialize()
{
    return "quit-request";
}
