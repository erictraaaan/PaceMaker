#pragma once
#include "mbed.h"
#include "pulse.h"

class voor {
    public:
        voor();
        ~voor();
        voor(pulse*);
        voor(pulse*, chamberData*);
        void startPace();
    private:
        pulse* voorPulse;
        chamberData* voorChamber;
        
};