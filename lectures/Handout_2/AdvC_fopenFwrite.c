#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

FILE *fp;
float data[10];

struct person{
	char name[10];
	int age;
};
struct person x;

int main(){

if((fp=fopen("file.data","w"))==NULL){
	perror("cannot open");
	exit(1);
}

if(fwrite(&data[3],sizeof(float),4,fp)!=4) perror("cannot write");

if(fwrite(&x,sizeof(x),1,fp)!=1) perror("cannot write");

exit(0);
}