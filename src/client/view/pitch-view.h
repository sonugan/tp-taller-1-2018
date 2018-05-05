#ifndef PITCHVIEW_H
#define PITCHVIEW_H

#include "../../shared/model/pitch.h"
#include "abstract-view.h"
#include "sprites-provider.h"
#include "shared-enums.h"

class PitchView : public AbstractView {
    public:
        PitchView(Pitch* pitch);
        virtual ~PitchView();
        void Render(int x_camera, int y_camera, int max_x, int max_y);
    protected:

    private:
        Pitch* pitch;
};

#endif // PITCHVIEW_H
