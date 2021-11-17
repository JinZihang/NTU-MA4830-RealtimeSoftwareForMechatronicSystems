#include <time.h>

#include "../main.h"

int *UpdateTimer() {
    int *dummy;
    struct itimerspec timerInfo;

    if (previousWave.waveform != wave.waveform
        && previousWave.amplitude != wave.amplitude
        && previousWave.frequency != wave.frequency) {
        timerInfo.it_value.tv_sec = 0;
        timerInfo.it_value.tv_nsec = 0;
        timerInfo.it_interval.tv_sec = 10;
        timerInfo.it_interval.tv_nsec = 0;
        return timer_settime(timerid, 0, &timerInfo, NULL);
    } else {
        return dummy;
    }
}
