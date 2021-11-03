#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int signum) {
    printf("\nSignal raised.\n");
}

int main(void) {
    unsigned int time_left;
    int rtn;

    signal(SIGALRM, alarm_handler);
    printf("Set the alarm and sleep\n");
    alarm(5);

    sleep(2);        //Sleep for 2 seconds
    time_left = alarm(0);
    printf("Time left before cancel, and rearm: %d\n", time_left);

    alarm(time_left);    // set an alarm to go off again
    printf("Hang around, waiting to return in %d secs\n", time_left);

    rtn = pause();        // suspend process until delivery of signal

    printf("Pause returned with %d.  Sleep for 5 secs\n", rtn);
    alarm(2);
    rtn = sleep(5);

    printf("Returned from sleep, only slept %d secs\n", 5 - rtn);
    return 0;
}
