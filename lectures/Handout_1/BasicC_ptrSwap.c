#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y){
	int temp;
	
	temp=*x;
	*x=*y;
	*y=temp;
}

void swapneg(int x, int y){
	int temp;
	
	temp=x;
	x=y;
	y=temp;
}

struct point{
	int x;
	int y;
};

int main(){
	int i=10, a=2, b=5;
	int *p;
	struct point s={2,3};
	struct point *pb;

	p=&i;
	printf("Value pointed by p = %d\n",*p); 

	*p=5;
	printf("Value of i = %d\n",i); 

	printf("Before swap:a = %d, b = %d\n",a,b);
	swap(&a,&b);
	printf("After swap:a = %d, b = %d\n",a,b); 

	swapneg(a,b);
	printf("After swapneg:a = %d, b = %d\n",a,b); 

	pb=&s;
	(*pb).y=8;//modify field
	pb->y=8;//equivalent statement

	const int result=5;
	//result=10;illegal
	printf("result=%d\n",result);

	const char *answer_ptr="Five";
	printf("Before answer_ptr=%s\n",answer_ptr);
	answer_ptr=(char *)0x1234;//legal
	printf("After answer_ptr=%s\n",answer_ptr);
	//*answer_ptr='X';illegal
	exit(0);
	
}