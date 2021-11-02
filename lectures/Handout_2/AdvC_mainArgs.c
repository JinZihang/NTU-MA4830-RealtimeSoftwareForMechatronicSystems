#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
int a_option=0, b_option=0;
char **p_to_arg=&argv[1];

while(--argc && (*p_to_arg)[0]=='-'){
	if((*p_to_arg)[1]=='\0'){
		printf("invalid option\n");
		exit(1);
		}
	
	switch((*p_to_arg)[1]){
		case 'a':a_option=1;
			 break;
		case 'b':b_option=1;
			 break;
		default:printf("invalid option\n");
			exit(1); 
		}
	p_to_arg++;
	}

	if(argc!=1){
		printf("invalid arguments\n");
		exit(1);
	}
	printf("a option:%s\n",(a_option)?"yes":"no");
	printf("b option:%s\n",(b_option)?"yes":"no");
	printf("file:%s\n",*p_to_arg);
	exit(0);
}