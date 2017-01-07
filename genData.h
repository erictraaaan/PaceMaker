#pragma once
#include "mbed.h"

class genData{
public:
    enum Mode
    {
        VVI,
        VOOR 
    };
    enum State
    {
        PERMANENT,
        TEMPORARY
    };
    
    genData();
    ~genData();
    void chngHyst(bool);
    bool getHyst();
    int chngHystRL(double);
    double getHystRL();
    int chngLRL(double);
    double getLRL();
    int chngURL(double);
    double getURL();
    int chngAVdelay(double);
    double getAVdelay();
    int chngAVdelayOffset(double);
    double getAVdelayOffset();
    int chngRSmooth(double);
    double getRSmooth();
    virtual void chngMode(Mode mode);
    virtual Mode getMode();
    virtual void chngState(State state);
    virtual State getState();
    //virtual bool isMagnet();
    //virtual void chngMagnet(bool state);

protected:
    double p_hysteresis;
    double p_hysteresisRateLimit;
    double p_lowerRateLimit;
    double p_upperRateLimit;
    double p_AVdelay;
    double p_AVdelayOffset;
    double p_rateSmoothing;
    Mode p_pacingMode;
    State p_pacingState;
    
};