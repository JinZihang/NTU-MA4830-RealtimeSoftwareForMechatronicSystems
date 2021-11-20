#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    int i;

    if ((fp = fopen("fopenFprintf.txt", "w")) == NULL) {
        perror("cannot open");
        exit(1);
    }

    for (i = 0; i < 6; i++)
        if (fprintf(fp, "%d\n", i) != 2) {
            perror("cannot write");
            exit(1);
        }
    fclose(fp);

    exit(0);
}