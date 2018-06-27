#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "igeometric-form.h"

using namespace std;

class Rectangle
{
    public:
        Rectangle(int x1, int x2, int y1, int y2);
        virtual ~Rectangle();
        bool IsInside(Location* location);
    protected:
    private:
        int x1;
        int x2;
        int y1;
        int y2;
};

#endif // RECTANGLE_H
