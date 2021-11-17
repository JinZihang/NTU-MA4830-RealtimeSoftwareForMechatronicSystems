#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
    if (previousWave.waveform != wave.waveform
        && previousWave.amplitude != wave.amplitude
        && previousWave.frequency != wave.frequency) {
        count_down = 0;
    }
}
