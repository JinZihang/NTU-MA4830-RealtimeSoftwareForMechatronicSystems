#include <stdio.h>
#include <stdlib.h>

float mean(int x,int y){
	float f;
	f=(x+y)/2.0;
	return f;
}

int main(){
	int a,b;
	float answer;

	a=3;b=2;
	answer=mean(a,b);
	printf("The mean of %d and %d is %f\n",a,b,answer);
	exit(0);
}