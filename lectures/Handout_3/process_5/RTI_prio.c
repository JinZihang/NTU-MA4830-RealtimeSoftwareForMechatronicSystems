//***********************************************************************
// 	Program : dm_prio.c
//
//	Demonstration of priority, scheduling & sleep
//  	sched_getparam(0, &param);
//  	sched_getscheduler( pid_t pid );
// 	sched_setscheduler (0, SCHED_FIFO, &param);
//
// 	28 Jan. 2007 : G.Seet
// 	QNX 6.xx version
//***********************************************************************
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/neutrino.h>
#include <process.h>
#include <unistd.h>
#include <sched.h>

int main(int argc, char *argv[]){
struct sched_param  params;
int policy;
			// Get Existing Setting
printf("\fScheduled Parameters\n");
printf("\nPolicy Constant : <SCHED_FIFO:%d><SCHED_RR%d><SCHED_OTHER:%d>\n",
	SCHED_FIFO,SCHED_RR,SCHED_OTHER);
sched_getparam(0, &params);

printf("The assigned priority is %d. and the current priority is %d\n", 
	params.sched_priority,params.sched_curpriority);

policy=sched_getscheduler(0);

printf("The assigned scheduler policy is %d\n", policy);
			// Change settings & Get Net Settings

printf("\n\nChanged Scheduled Parameters\n");

params.sched_priority+=1;			
			// increase scheduled priority

sched_setscheduler(0,2,&params);		
			// sets priority & scheduler policy

sched_getparam(0, &params);

printf("The assigned priority is %d. and the current priority is %d\n",
	params.sched_priority,params.sched_curpriority);

policy=sched_getscheduler(0);
printf("The assigned scheduler policy is %d\n",policy);

return(EXIT_SUCCESS);
}

