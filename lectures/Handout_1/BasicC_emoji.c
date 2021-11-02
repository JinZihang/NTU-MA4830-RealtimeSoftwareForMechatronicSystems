#include <stdio.h>
#include <stdlib.h>

int main(){

char data[]={0x18,0x18,0x18,0xff,0xff,0x18,0x18,0x18};
char msk;
int i,j;

for(i=0;i<8;i++){
	for(j=0;j<8;j++){
	msk=1<<(7-j);
	if((data[i]&msk)==0) putchar('0');
	else putchar('1');
}
putchar('\n');
}

}