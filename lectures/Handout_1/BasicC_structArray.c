#include <stdio.h>
#include <stdlib.h>

struct point{
	int x;
	int y;
};

union option{
	int number;
	float price;
};
 
typedef int integer;
typedef int array[100];
typedef struct point Point;

int main(){
	int i;
	union option xo;//assigning 'x' results in error dur to conflicts
	struct point a,b;
	integer x;
	array d;
	Point e;
	Point c[10];
	
	a.x = 12; b=a;

	xo.number=13;//assign value to union members negative example
	xo.price=12.5;
	printf("xo.number = %d\n",xo.number); 
	printf("xo.price = %f\n",xo.price); 

	xo.number=13;
	printf("xo.number = %d\n",xo.number); 
	xo.price=12.5;
	printf("xo.price = %f\n",xo.price); 

	printf("a.x = %d\n",a.x); 
	printf("a.y = %d\n",a.y); 	
	printf("b.x = %d\n",b.x); 
	printf("b.y = %d\n",b.y); 

	x=10;
	printf("x = %d\n",x);

	for(i=0;i<100;i++){
		d[i]=i;
		printf("d[%d]=%d\n",i,d[i]);
	}
	
	e.x=27;
	e.y=13;

	printf("e.x = %d\n",e.x); 
	printf("e.y = %d\n",e.y); 

	for(i=0;i<10;i++){
		c[i].x=30;
		c[i].y=17;
		printf("c[%d].x=%d, c[%d].y=%d\n",i,c[i].x,i,c[i].y);
	}
	exit(0);
	
}