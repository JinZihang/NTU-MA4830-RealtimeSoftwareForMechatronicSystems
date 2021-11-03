#include <stdio.h>
#include <stdlib.h>

int main(){
	int i,b,a,x;
	
	i=10; printf("i = %d\n",i++); 
	i=10; printf("i = %d\n",++i); 
	i=(b=1+2)+4; printf("i = %d\n",i); 
	i=(3<=8)+4; printf("i = %d\n",i); 
	i=(1<<1); printf("i = %d\n",i); 
	a=(x<2)? 5 : 12; printf("a = %d\n",a); // assume x = 2 
	
}