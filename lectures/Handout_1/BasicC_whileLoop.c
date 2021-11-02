#include <stdio.h>
#include <stdlib.h>

int main(){
	int i=1,sum=0;

	while(i<5){
	sum +=i;
	i++;
	}
	printf("Summation is %d\n",sum);
	exit(0);
}