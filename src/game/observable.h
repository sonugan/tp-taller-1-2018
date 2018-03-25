#ifndef OBSERVABLE_H_INCLUDED
#define OBSERVABLE_H_INCLUDED

#include "observer.h"

class Observable
{
public:
    virtual AddObserver(Observer o);
};


#endif // OBSERVABLE_H_INCLUDED
