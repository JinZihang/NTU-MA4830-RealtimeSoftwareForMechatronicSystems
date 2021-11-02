#include <stdio.h>
#include <stdlib.h>

int main(){
	int i,c;
	int n_spaces=0,n_symbols=0,n_chars=0;

	for(i=0;i<50;i++){
		c=getchar();
		if(c==EOF) break;
		if(c=='\n') continue;

		switch(c){
			case ' ': n_spaces++;
				  break;
			case ',':
			case '.':
			case ';': n_symbols++;
			default : n_chars++;
		}
			
	}
	printf("Chars: %d spaces: %d symbols %d\n",n_chars,n_spaces,n_symbols);
	exit(0);
}