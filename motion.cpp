#include "rtos.h"
#include "FXOS8700Q.h"
#include "mbed.h"
#include "hardware.h"
#include "pulse.h"
#include "chamberData.h"


FXOS8700Q_acc acc(PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1);
//DigitalOut red(LED_RED);


/* Constants and Declares */
int numCount;
int numCount2;
chamberData* ventChamber;
chamberData* atrChamber;
int const MAX_NUM_COUNTS = 3;
int const MIN_NUM_COUNTS = 3;
int const TIMING_PERIOD = 20; // Sensor polling interval

uint8_t motion_exceeded_threshold = 0;

void initialize_motion () {
    acc.enable();
}

void motion_set_chamber(int i, chamberData* c){
    if (i == 0)
    ventChamber = c;
        
}

//bool isMotionThresholdExceeded () {
//    return motion_exceeded_threshold;    
//}
//
//void resetMotionDetection () {
//    motion_exceeded_threshold = 0;
//}

/**** Function: a_count
 * return: void
 * parameters: none
 * A function called if motion detection interrupt flag is set.  Maintains
 * a global counter and sets a timer to keep track of number of flags within
 * timing limit.
 */ 
void a_count(void) {
    /* step 1 increment the counter */
    numCount++;
    

    if (numCount >= MAX_NUM_COUNTS) {
        ventChamber->chngPaceWidth(ventChamber->getPaceWidth() - 0.01);
        numCount = 0;
 //       red = !red;   // toggle LEDs to show acceleration threshold reached
        
        motion_exceeded_threshold = 1;
    }
}

void b_count(){
    numCount2++;
    
    if (numCount2 >= MIN_NUM_COUNTS){
        ventChamber->chngPaceWidth(ventChamber->getPaceWidth() + 0.01);
        numCount2 = 0;
  //      red = !red;
    }
}

void motion_thread () {
    while(true) {
  //      red = !red;
        float xAcc, yAcc, zAcc;
        acc.getX(&xAcc);
        acc.getY(&yAcc);
        acc.getZ(&zAcc);
        float magtd = xAcc*xAcc + yAcc*yAcc + zAcc*zAcc;
        
        if (magtd > 3.0f) { // Greater than (1.5G of Accel.)^2
            a_count();      // increment acceleration event counter
        }

        if (magtd < 1.5f){
            b_count();
        Thread::wait(TIMING_PERIOD); 
        }
    }   
}
