#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "igeometric-form.h"

using namespace std;

class Rectangle
{
    public:
        Rectangle(Location* leftmost_highest_point, int height, int base);
        virtual ~Rectangle();
        bool IsInside(Location* location);
        void Move(Location* location);
        Location* GetLeftmostHighestPoint();
    protected:
    private:
        int base;
        int height;
        Location* leftmost_highest_point;
};

#endif // RECTANGLE_H
