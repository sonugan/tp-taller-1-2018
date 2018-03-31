#ifndef PITCHVIEW_H
#define PITCHVIEW_H

#include "pitch.h"
#include "../common/abstract-view.h"

class PitchView : public AbstractView {
    public:
        PitchView(Pitch* pitch, SDL_Renderer* renderer);
        virtual ~PitchView();
        void Render(int xCamera, int yCamera, int maxX, int maxY);
    protected:

    private:
        Pitch* pitch;
};

#endif // PITCHVIEW_H
