#ifndef IGEOMETRIC_FORM_H
#define IGEOMETRIC_FORM_H

#include <string>
#include <vector>
#include <iostream>
#include "../model/location.h"

using namespace std;

class IGeometricForm
{
    public:
        IGeometricForm();
        virtual ~IGeometricForm();
        virtual bool ExistsCollision2d(IGeometricForm other_form){};
        virtual bool ExistsCollision3d(IGeometricForm other_form){};
    protected:
    private:
};

#endif // IGEOMETRIC_FORM_H
