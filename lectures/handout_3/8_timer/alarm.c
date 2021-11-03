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

    signal(SIGALRM, alarm_handler); // a good practice to put it at the start

    printf("Set the alarm and sleep\n");
    alarm(5);
    sleep(2); // sleep for 2 seconds

    time_left = alarm(0); // alarm(0) clears the alarm
    printf("Time left before cancel, and rearm: %d\n", time_left);

    alarm(time_left); // set an alarm to go off again
    printf("Hang around, waiting to return in %d secs\n", time_left);

    rtn = pause(); // suspend process until delivery of signal
    printf("Pause returned with %d. Sleep for 5 secs\n", rtn);

    alarm(2); // send an alarm 2 seconds later
    rtn = sleep(5); // this thread starts to sleep
    // then at t=2s, an alarm is sent, the thread is woken up, rtn is only 2
    printf("Returned from sleep, only slept %d secs\n", 5 - rtn); // here rtn is the time elapsed

    return 0;
}
