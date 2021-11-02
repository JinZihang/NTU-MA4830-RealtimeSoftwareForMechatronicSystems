#include <stdio.h>
#include <stdlib.h>
int sum,i;

int main(){
	
	for(sum=0,i=1;i<5;i++){
	
	sum +=i;
	
	}

	printf("Summation is %d\n",sum);
	exit(0);
}