#pragma once
#include "mbed.h"
#include "sense.h"
#include "pulse.h"
#include "chamberData.h"


void vvi_set_chamber(pulse* c,chamberData* d, sense* e);

void start_VVI();