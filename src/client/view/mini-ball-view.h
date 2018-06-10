#ifndef MINIBALLVIEW_H
#define MINIBALLVIEW_H

#include "../../shared/model/ball.h"
#include "abstract-view.h"
#include "ishowable.h"
#include "sprites-provider.h"
#include "camera.h"

class MiniBallView: public AbstractView
{
    public:
        MiniBallView(Ball* ball, int real_pitch_height, int real_pitch_width);
        virtual ~MiniBallView();
        void Render(int x_camera, int y_camera, int max_x, int max_y);
    protected:

    private:

        static const int MINI_PITCH_OFFSET_X = 338; // DONDE EMPIEZA LA CANCHA EN EL PANEL DE INFORMACION
        static const int MINI_PITCH_OFFSET_Y = 0; // DONDE EMPIEZA LA CANCHA EN EL PANEL DE INFORMACION

        static const int MINI_PITCH_WIDTH = 124;
        static const int MINI_PITCH_HEIGHT = 65;

        static const int MINI_BALL_WIDTH = 20;
        static const int MINI_BALL_HEIGHT = 20;

        // MARGENES PARA QUE LA PELOTA REAL QUEDE CENTRADA EN EL CUADRADO
        static const int MINI_BALL_Y_MARGIN = 8;
        static const int MINI_BALL_X_MARGIN = 8;

        Ball* ball;
        int real_pitch_height;
        int real_pitch_width;

        int GetMiniBallX();
        int GetMiniBallY();


};

#endif
