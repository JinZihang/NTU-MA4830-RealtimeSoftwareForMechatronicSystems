//**************************************************************************
//	Program : pt_create.c
//	Demonstrates simple thread process.
// 	Threads drop out of the procedure when done. Threads have access to 
// 	current process's code and data.
//
//	Revised for QNX6.3 : 4 November 2010
//
//**************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <process.h>

int main(int,char *[]);
int global;

void * thread(void *arg)
 {
for(;;)
 {
  printf("Thread process : %d\n",global++);
  sleep(2);
  }
}

int main(int argc,char *argv[])
 {
pthread_attr_t attr;



printf("Starting a thread from main\n");
sleep(1);

pthread_create( NULL, NULL, &thread, NULL );
for(;;)
 {
  printf("Main process   : %d\n",global++);
  sleep(1);
  }
return(EXIT_SUCCESS);
}

