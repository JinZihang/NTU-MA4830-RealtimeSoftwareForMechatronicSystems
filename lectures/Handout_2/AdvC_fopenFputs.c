#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
int i;
FILE *fp;
char *str[]={"one","two","three"};

if ((fp=fopen("file.dat","w"))==NULL){
	perror("cannot open");
	exit(1);
	}

for(i=0;i<3;i++)
	if(fputs(str[i],fp)==EOF){
		printf("Cannot write");
		exit(1);
		}
fclose(fp);
exit(0);
}