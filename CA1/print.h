#ifndef PRINT
#define PRINT

#define MAX_LEN 128

void print_image(FILE *fptr)
{
    char read_string[MAX_LEN];

    while (fgets(read_string, sizeof(read_string), fptr) != NULL)
        printf("%s", read_string);
}

#endif