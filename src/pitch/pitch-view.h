#ifndef PITCHVIEW_H
#define PITCHVIEW_H

#include "pitch.h"
#include "../common/sprite-sheet.h"

class PitchView
{
    public:
        PitchView(Pitch* pitch);
        virtual ~PitchView();

    protected:

    private:
        Pitch* pitch;
        SpriteSheet* sprite_sheet;
};

#endif // PITCHVIEW_H
