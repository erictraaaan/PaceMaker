#pragma once
#include "mbed.h"

//bool isMotionThresholdExceeded ();
//void resetMotionDetection ();
void initialize_motion ();
void motion_thread ();
void motion_set_chamber(int, chamberData*);
   
