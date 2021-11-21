#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int count;

void alarm_handler(int signum) {
    ++count;
}

int main(void) {
    char input[80];
    timer_t timerid;
    struct timespec now;     // time structure
    struct itimerspec timer; // timer structure
    long timesec, timeint;
    int rtn;

    signal(SIGALRM, alarm_handler);

    // create a timer binding to the event
    if (timer_create(CLOCK_REALTIME, NULL, &timerid) == -1) {
        printf("Error: failed to create timer\n");
        exit(-1);
    }

    // after 1s, the first signal will occur and after 2s, the same signal will occur periodically
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_nsec = 0;

    timer.it_interval.tv_sec = 2;
    timer.it_interval.tv_nsec = 0;

    rtn = timer_settime(timerid, 0, &timer, NULL);
    if (rtn == -1) {
        printf("\nError setting timer!\n\n");
        exit(1);
    }

    while (1) {
        printf("Global Count %d\n", count);
        sleep(1);
    }

    timer_delete(timerid);
    exit(0);
}
