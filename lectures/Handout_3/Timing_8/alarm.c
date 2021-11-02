#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


//Procedure: 
//		compile and run 

void alarm_handler( int signum ) {
  printf( "\nSignal raised.\n" );
  }

int main( void ) {
  unsigned int timeleft;
  int rtn;
	
  signal( SIGALRM, alarm_handler ); 
  printf("Set the alarm and sleep\n" );
  alarm(5);
  
sleep( 2 ); 		//Sleep for 2 seconds
timeleft = alarm( 0 );
printf( "Time left before cancel, and rearm: %d\n", timeleft );

alarm( timeleft ); 	// set an alarm to go off again
printf("Hang around, waiting to return in %d secs\n", timeleft );

rtn = pause();      	// suspend process until delivery of signal

printf( "Pause returned with %d.  Sleep for 5 secs\n", rtn );
alarm( 2 );
rtn = sleep(5);

printf( "Returned from sleep, only slept %d secs\n", 5-rtn );
return 0;
}
