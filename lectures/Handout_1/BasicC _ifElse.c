#include <stdio.h>
#include <stdlib.h>

float rate(float hours){
	float f;

	if(hours<10.0) f=1.5*hours;//rate 1
	else if(hours<15.0)	f=2.0*hours;//rate 2
	     else f=2.5*hours;//rate 3
	return f;
}

int main(){
	float hours,cost;
	
	hours = 10.1;
	cost = rate(hours);
	printf("Your bill for %f hours usage is $%f\n",hours,cost);
	exit(0);
}