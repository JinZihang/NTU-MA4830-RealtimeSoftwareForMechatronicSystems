#include <stdlib.h>
#include <stdio.h>

#define MAX_LEN 128

void DisplayImage(FILE *fptr)
{
    char readString[MAX_LEN];

    while (fgets(readString, sizeof(readString), fptr) != NULL)
        printf("%s", readString);
}

void DisplayTitle(char *filename)
{
    FILE *fptr = NULL;

    if ((fptr = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Error opening %s!\n", filename);
        exit(1);
    }
    DisplayImage(fptr);
}
