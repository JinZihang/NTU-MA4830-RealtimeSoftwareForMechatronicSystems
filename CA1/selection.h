#ifndef SELECTION
#define SELECTION

#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "print.h"

int DimensionSelection() {
    PrintDimensionSelection();

    char *input;

    while(true) {
        if((input=(char *)malloc(100 * sizeof(char))) == NULL) {
            NoMemoryAlert();
            return -1;
        }

        scanf("%99s", input);

        char *inputLowercase = strdup(input);
        unsigned char *char_ptr = (unsigned char *)inputLowercase;
        while(*char_ptr) {
            *char_ptr = tolower(*char_ptr);
            char_ptr++;
        }

        if (strcmp(inputLowercase, "2d") == 0 || strcmp(inputLowercase, "1") == 0) {
            free(input);
            free(inputLowercase);
            free(char_ptr);
            return 2;

        } else if (strcmp(inputLowercase, "3d") == 0 || strcmp(inputLowercase, "2") == 0) {
            free(input);
            free(inputLowercase);
            free(char_ptr);
            return 3;

        } else if (strcmp(inputLowercase, "exit") == 0) {
            free(input);
            free(inputLowercase);
            free(char_ptr);
            return -1;

        } else {
            WrongDimensionInput();
        }

        free(input);
        free(inputLowercase);
        free(char_ptr);
    }
}

#endif
