#ifndef ILOCATABLE_H
#define ILOCATABLE_H

#include "location.h"

class ILocatable
{
    public:
        virtual Location* GetLocation(){ return this->location; };
        virtual ~ILocatable () {};
    protected:
        Location* location;
    private:
};

#endif // ILOCATABLE_H
