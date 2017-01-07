#pragma once
#include "mbed.h"
#include "genData.h"

class chamberData : public genData {
public:
    chamberData();
    ~chamberData();
    chamberData(char);
    char getChamberType();
    int chngPaceAmp(double);
    double getPaceAmp();
    int chngPaceWidth(double);
    double getPaceWidth();
    int chngRP(double);
    double getRP();
    int chngSensitivity(double);
    double getSensitivity();
    void setMarker(char);
    char getMarker();
    
private:
    char mychamber;
    char f_marker;
    double p_PaceAmp;
    double p_PaceWidth;
    double p_RP;
    double p_Sensitivity;
    
};