#ifndef MINIPLAYERVIEW_H
#define MINIPLAYERVIEW_H

#include "../../shared/model/player.h"
#include "abstract-view.h"
#include "ishowable.h"
#include "sprites-provider.h"
#include "camera.h"

class MiniPlayerView: public AbstractView
{
    public:
        MiniPlayerView(Player* Player, int real_pitch_height, int real_pitch_width);
        virtual ~MiniPlayerView();
        void Render(int x_camera, int y_camera, int max_x, int max_y);
    protected:

    private:
        static const int MINI_PITCH_OFFSET_X = 338; // DONDE EMPIEZA LA CANCHA EN EL PANEL DE INFORMACION
        static const int MINI_PITCH_OFFSET_Y = 0; // DONDE EMPIEZA LA CANCHA EN EL PANEL DE INFORMACION
        static const int MINI_PITCH_WIDTH = 124;
        static const int MINI_PITCH_HEIGHT = 65;
        static const int TEAM_OFFSET = 2;

        Player* player;
        int real_pitch_height;
        int real_pitch_width;

        int GetMiniPlayerX();
        int GetMiniPlayerY();

};

#endif // MINI-PLAYER-VIEW_H
