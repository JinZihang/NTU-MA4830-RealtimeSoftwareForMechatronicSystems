//**********************************************************************
// signal - Demostrated the seting up of a periodic timer and its use
//				
// Functions: timercreate, timersettime, signal
//
// October 2010, G.Seet
//**********************************************************************

#include <stdio.h>
#include <signal.h>

int signal_count, signal_number;

void signal_handler( int signum ) {
    printf( "\nSignal raised. " );
    ++signal_count;
    signal_number = signum;
   }

int  main(){
unsigned long i;
signal_count = 0; 
signal_number = 0;

signal( SIGINT, signal_handler );
printf("Signal raised on CTRL-C\n" ); 

printf( "Iteration:         " );
for( i = 0; i < 100000; i++ ) {
   printf( "\b\b\b\b\b\b%6d", i );
   flushall( );

   if( i == 90000 ) raise( SIGINT );
   if( signal_count > 0 ) break;
   }

   if (i==100000) printf( "\nNo signal was raised.\n" );
  else if( i == 90000 ) printf("\nSignal %d was raised by raise() function.\n", signal_number );
  else printf( "\nUser raised the signal.\n" );
}
