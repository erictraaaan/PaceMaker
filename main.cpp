#pragma once
#include "mbed.h"
#include "chamberData.h"
#include "genData.h"
#include "pulse.h"
#include "hardware.h"
#include "interface.h"
#include "voor.h"
#include "sense.h"
#include "motion.h"
#include "VVI.h"

int main(){
    hardware* io = new hardware();
    genData* generalData = new genData();
    chamberData* atrium = new chamberData('a');
    chamberData* ventricle = new chamberData('v');
    pulse* ventPulse = new pulse(ventricle,io);
    pulse* atrPulse = new pulse(atrium,io);
    sense* isSense = new sense(generalData);
    
    
    Thread vviThread(osPriorityNormal);
    vvi_set_chamber(atrPulse,atrium,isSense);
    vviThread.start(start_VVI);
    
    Thread motionThread(osPriorityBelowNormal);
    initialize_motion ();
    motion_set_chamber(0, ventricle);
    motionThread.start(motion_thread);

    
    interface a(io->getSerial() , ventPulse , generalData, atrium , ventricle,io); 
    
    a.readValues();   
    
    
    delete ventricle; //code never reaches here, since we're stuck in the while loops of the pacing, user interface, etc.
    delete atrium;
    delete ventPulse;
    delete atrPulse;
    delete isSense;
    delete io;
    
return 0;
    }