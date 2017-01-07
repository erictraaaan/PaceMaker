#include "rtos.h"
#include "mbed.h"
#include "hardware.h"
#include "pulse.h"
#include "chamberData.h"
#include "pulse.h"
#include "VVI.h"
#include "sense.h"

DigitalOut green(LED_GREEN);

pulse* chamberPulse;
chamberData* myChamber;
sense* mySense;

void vvi_set_chamber(pulse* c, chamberData* d, sense* e){
    chamberPulse = c;
    myChamber = d; 
    mySense = e; 
}

void start_VVI(){
    while(true){
        green = !green;
        myChamber->setMarker('x');
        bool sensed = mySense->returnedSense();
        if(!sensed){
            chamberPulse->startPulse();
            myChamber->setMarker('p');
        }
        else{
            myChamber->setMarker('s');
        }
        Thread::wait(myChamber->getRP());
        }
}

