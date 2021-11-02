#include <stdio.h>
#include <stdlib.h>

int main(){
	int i=1,sum=0;

	do{
	sum +=i;
	i++;
	}while(i<5);

	printf("Summation is %d\n",sum);
	exit(0);
}