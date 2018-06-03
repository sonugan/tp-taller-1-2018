#ifndef SHADOW_H
#define SHADOW_H

#include <vector>
#include "circle.h"
#include "../model/player.h"

using namespace std;

class Player;
class Shadow
{
    public:
        Shadow(Player* player);
        virtual ~Shadow();
        bool CollidesWith(Shadow* other_shadow);
        void PlayerHasChanged();
        bool CanMoveTo(Location* location);
        Circle* GetCircle();
    protected:
    private:
        Circle* circle;
        Player* player;
};

#endif // SHADOW_H
