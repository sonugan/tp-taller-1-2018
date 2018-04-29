#ifndef ISHOWABLE_H
#define ISHOWABLE_H

#include "../../shared/model/location.h"

class IShowable
{
    public:
        virtual Location* GetLocation(){ return NULL;};
        virtual void SetWidth(float width){ this->width = width; }
        virtual void SetHeight(float height){ this->height = height; }
        virtual float GetWidth(){ return this->width; }
        virtual float GetHeight(){ return this->height; }
    protected:
        float width;
        float height;
    private:
};

#endif // ISHOWABLE_H
