#ifndef INFOPANELVIEW_H
#define INFOPANELVIEW_H

#include "abstract-view.h"
#include "sprites-provider.h"


class InfoPanelView : public AbstractView
{
    public:
        InfoPanelView();
        virtual ~InfoPanelView();
        void Render(int x_camera, int y_camera, int max_x, int max_y);
    protected:

    private:
        static const int SPRITE_WIDTH = 800;
        static const int SPRITE_HEIGHT = 78;
};

#endif // INFO-PANEL-VIEW_H
