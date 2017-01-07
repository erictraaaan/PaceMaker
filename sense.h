#pragma once
#include "mbed.h"
#include "genData.h"

class sense{
    public:
        sense(genData*);
        ~sense();
        void checkHrt();
        void getPulse();
        bool returnedSense();
    
    private:
        bool isSensed;
        bool timeout;
        genData* myGenData; 
        AnalogIn mySense;
};