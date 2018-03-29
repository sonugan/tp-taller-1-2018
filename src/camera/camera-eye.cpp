#include "camera-eye.h"

CameraEye::CameraEye(unsigned int xStartPosition, unsigned int yStartPosition, unsigned int width, unsigned int height)
{
    this->area = new SDL_Rect();
    this->area->x = xStartPosition;
    this->area->y = yStartPosition;
    this->area->w = width;
    this->area->h = height;
}

CameraEye::~CameraEye()
{
    delete this->area;
}

unsigned int CameraEye::GetXStartPosition()
{
    return this->area->x;
}

unsigned int CameraEye::GetYStartPosition()
{
    return this->area->y;
}

unsigned int CameraEye::GetWidth()
{
    return this->area->w;
}

unsigned int CameraEye::GetHeight()
{
    return this->area->h;
}

void CameraEye::SetXStartPosition(unsigned int value)
{
    this->area->x = value;
}
void CameraEye::SetYStartPosition(unsigned int value)
{
    this->area->y = value;
}
