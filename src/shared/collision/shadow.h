#ifndef SHADOW_H
#define SHADOW_H

#include <vector>
#include <limits>
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
        Location* GetBestNextPosition(Location* target, int speed);
    protected:
    private:
        Circle* circle;
        Player* player;
        static const u_int HALO_RADIUS = 10;

        void IsBetterAlternative(Location* possible_location, float distance_to_target, Location* best_location, float* best_distance);
};

#endif // SHADOW_H
