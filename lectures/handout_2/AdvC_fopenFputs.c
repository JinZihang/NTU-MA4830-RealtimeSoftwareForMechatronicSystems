#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int i;
    FILE *fp;
    char *str[] = {"one\n", "two\n", "three\n"};

    if ((fp = fopen("fopenFputs.txt", "w")) == NULL) {
        perror("cannot open");
        exit(1);
    }

    for (i = 0; i < 3; i++)
        if (fputs(str[i], fp) == EOF) {
            printf("Cannot write");
            exit(1);
        }
    fclose(fp);

    exit(0);
}