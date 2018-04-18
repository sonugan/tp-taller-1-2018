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
        //  La imagen de la cancha es de 1920x1080.
        //  Se le resta 32 porque la ubicación del jugador no es la misma que la del sprite
        //  (hay un offset de 32 píxeles).
        static const int MAX_X_LOCATION = 1888;
        static const int MIN_X_LOCATION = -32;
        static const int MAX_Y_LOCATION = 1048;
        static const int MIN_Y_LOCATION = -32;
        int x;
        int y;
        int z;
};

#endif // LOCATION_H
