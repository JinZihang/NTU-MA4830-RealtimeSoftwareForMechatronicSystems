#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

int (*p)(int, int);

int add(int x, int y){
return x+y;
}

int sub(int x, int y){
return x-y;
}

p=add;
printf("%d\n",(*p)(2,3));

p=sub;
printf("%d\n",(*p)(2,3));

exit(0);
}