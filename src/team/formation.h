#ifndef FORMATION_H
#define FORMATION_H

#include <vector>
#include <iostream>
#include "../common/location.h"

enum FORMATION { F_3_3, F_3_1_2, F_3_2_1 };
class Formation
{
    public:
        Formation(FORMATION value);
        virtual ~Formation();
        Location* GetLocationForPlayer(unsigned int player_index);
        FORMATION GetValue();

    protected:

    private:
        FORMATION value;
        std::vector<Location*> positions;
};

#endif // FORMATION_H
