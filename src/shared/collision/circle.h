#ifndef CIRCLE_H
#define CIRCLE_H

#include "igeometric-form.h"

using namespace std;

class Circle
{
    public:
        Circle(int radius, Location* center);
        virtual ~Circle();
        bool ExistsCollision2d(Circle* other_circle);
        bool ExistsCollision3d(Circle* other_circle);
        void Move(Location* location);
        Location* GetCenter();
    protected:
    private:
        int radius;
        Location* center;
};

#endif // CIRCLE_H
