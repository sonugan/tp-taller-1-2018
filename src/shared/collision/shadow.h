#ifndef SHADOW_H
#define SHADOW_H

#include <vector>
#include "circle.h"
#include "../model/player.h"

using namespace std;

class Shadow
{
    public:
        Shadow(Location* masa_center);
        virtual ~Shadow();
        void AddForm(Circle* circle);
        bool CollidesWith(Shadow* other_shadow);
        void Move(Location* location);
    protected:
    private:
        vector<Circle*> forms;
        Location* masa_center;
};

#endif // SHADOW_H
