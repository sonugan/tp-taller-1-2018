#ifndef LOCATION_H
#define LOCATION_H

#include <math.h>
#include <string>

class Location
{
    public:
        Location(int x, int y, int z);
        Location(Location* location);
        virtual ~Location();
        int GetX();
        int GetY();
        int GetZ();
        void Update(int x, int y, int z);
        void UpdateX(int x);
        void UpdateY(int y);
        void UpdateZ(int z);
	    void Update(Location* location);
        float Distance(Location* other_location);
        float ManhattanDistance(Location* other_location);
        std::string ToString();

    protected:

    private:

	static const int MAX_X_LOCATION = 1920;
	static const int MIN_X_LOCATION = 0;
	static const int MAX_Y_LOCATION = 1080;
	static const int MIN_Y_LOCATION = 0;
        int x;
        int y;
        int z;
};

#endif // LOCATION_H
