#ifndef CAMERAEYE_H
#define CAMERAEYE_H

#include <SDL2/SDL.h>

class CameraEye
{
    public:
        CameraEye(unsigned int xStartPosition, unsigned int yStartPosition, unsigned int width, unsigned int height);
        virtual ~CameraEye();
        unsigned int GetXStartPosition();
        unsigned int GetYStartPosition();
        unsigned int GetWidth();
        unsigned int GetHeight();
        void SetXStartPosition(unsigned int value);
        void SetYStartPosition(unsigned int value);
    protected:
    private:
        SDL_Rect* area;
};

#endif // CAMERAEYE_H
