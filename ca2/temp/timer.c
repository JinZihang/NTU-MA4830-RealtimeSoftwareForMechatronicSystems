#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int count;

void alarm_handler(int signum)
{
  printf("Alarm Handler raised! ");

  // dynamic change over here 

  ++count;
}

int main(void)
{
  char input[80];
  timer_t timerid;    // the error here is caused by package problem
  struct timespec now;     // Time structure
  struct itimerspec timer; // Timer structure
  long timesec, timeint;
  int rtn;

  signal(SIGALRM, alarm_handler);   // the error here is caused by package problem
  // associate

  // *****************
  // Create the timer, binding to the event
  if (timer_create(CLOCK_REALTIME, NULL, &timerid) == -1)
  {
    printf("Error: failed to create timer\n");
    exit(-1);
  }

  //*************After 1s, the first signal will occur and after 10s, the same signal will occur periodly
  timer.it_value.tv_sec = 1;
  timer.it_value.tv_nsec = 0;

  timer.it_interval.tv_sec = 10;
  timer.it_interval.tv_nsec = 0;

  //*************
  rtn = timer_settime(timerid, 0, &timer, NULL);
  if (rtn == -1)
  {
    printf("\nError setting timer!\n\n");

    exit(1);
  }
  //************incremented by the signal handler
  while (1)
  {
    printf("Global Count %d\n", count);
    sleep(1);
  }

  timer_delete(timerid);
  return 0;
}
