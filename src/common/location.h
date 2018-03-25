#ifndef LOCATION_H
#define LOCATION_H


class Location
{
    public:
        Location(int x, int y, int z);
        virtual ~Location();
        int GetX();
        int GetY();
        int GetZ();
        void Update(int x, int y, int z);
        void UpdateX(int x);
        void UpdateY(int y);
        void UpdateZ(int z);

    protected:

    private:
        int x;
        int y;
        int z;
};

#endif // LOCATION_H
