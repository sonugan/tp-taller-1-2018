#ifndef LOCATION_H
#define LOCATION_H


class Location
{
    public:
        Location(int x, int y, int z);
        virtual ~Location();
        int getX();
        int getY();
        int getZ();
        void update(int x, int y, int z);

    protected:

    private:
        int x;
        int y;
        int z;
};

#endif // LOCATION_H
