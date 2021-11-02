#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
int fd;
char *str="Data";
int n=strlen(str)+1;

if ((fd=open("file.dat",O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR))<0){
	perror("cannot open");
	exit(1);
	}

if (write(fd,str,n)!=n){
	printf("Cannot write");
	exit(1);
	}
exit(0);
}