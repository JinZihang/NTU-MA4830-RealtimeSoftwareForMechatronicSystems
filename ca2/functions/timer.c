#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#include "../datatypes/struct.h"
#include "print.h"
#include "../main.h"

void TimerInitialization() {
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_nsec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_nsec = 0;
    if (timer_settime(timerid, 0, &timer, NULL) == -1) {
        Error_CannotSetTimer();
        exit(1);
    }
}

void *UpdateTimer() {
    struct Wave previousWave = wave;
    while(1) {
        if ((previousWave.waveform != wave.waveform)
            || (fabs(previousWave.amplitude - wave.amplitude) > 0.01)
            || (fabs(previousWave.frequency - wave.frequency) > 0.01)
            || (fabs(previousWave.duty_cycle - wave.duty_cycle) > 1)) {
            count_down = 30;
        }
        previousWave = wave;
        delay(10);
    }
}
