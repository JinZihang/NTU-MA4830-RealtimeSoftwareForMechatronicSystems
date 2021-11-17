#include <stdlib.h>
#include <stdio.h>

#include "../datatypes/struct.h"

#include "../main.h"

#define MAX_LEN 128

void DisplayImage(FILE *fptr) {
    char readString[MAX_LEN];

    while (fgets(readString, sizeof(readString), fptr) != NULL)
        printf("%s", readString);
    printf("\n\n");
}

void DisplayTitle(char *filename) {
    FILE *fptr = NULL;

    if ((fptr = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening %s!\n", filename);
        exit(1);
    }
    DisplayImage(fptr);
}

void ArgumentInstructions() {
    printf("help\n");
    printf("\t\t--h\t\tshow program argument instructions\n");
    printf("\t\t--fp\t\trun the program based on the data from a specific file\n");
    printf("\t\t--w\t\tselect a waveform (sine/rectangle/triangle/sawtooth) (default is sine)\n");
    printf("\t\t--a\t\treplace the default wave amplitude with your own value (default is 1)\n");
    printf("\t\t--f\t\treplace the default wave frequency with your own value (default is 100)\n");
    printf("notes\n");
    printf("\t\t*\t--h, --fp cannot be used together with other arguments\n");
    printf("\t\t*\tincomplete or duplicate declarations are not allowed\n");
    printf("\t\t*\twave amplitude and frequency arguments only accept positive numeric values\n");
    printf("\t\t*\tthe allowed maximum amplitude and frequency are 2.5 and 300 correspondingly (if the input value\n");
    printf("\t\t\tis greater than the allowed maximum value, program will continue with the maximum value)\n");
    printf("\t\t*\tfile\n");
    printf("\t\t\t\t**\teach row defines a wave, maximum 10 rows\n");
    printf("\t\t\t\t**\tthe first column defines waveform,\n");
    printf("\t\t\t\t\t\t1 -> sine\n\t\t\t\t\t\t2 -> rectangle\n\t\t\t\t\t\t3 -> triangle\n\t\t\t\t\t\t4 -> sawtooth\n");
    printf("\t\t\t\t\tthe second column defines wave amplitude,\n");
    printf("\t\t\t\t\tand the third column defines wave frequency\n");
    printf("\t\t\t\t\t(use 0 for default settings)\n");
    printf("\t\t\t\t**\tfile example\n");
    printf("\t\t\t\t\t--------------------\n");
    printf("\t\t\t\t\t../data.dat\n");
    printf("\t\t\t\t\t--------------------\n");
    printf("\t\t\t\t\t0\t\t0\t\t0\n");
    printf("\t\t\t\t\t3\t\t3\t\t0\n");
    printf("\t\t\t\t\t1\t\t1.25\t\t300\n");
    printf("\t\t\t\t\t1\t\t0\t\t60\n");
    printf("\t\t\t\t\t--------------------\n");
    printf("examples\n");
    printf("\t\t*\tvalid:\t\t./main --fp=../data.dat\n\t\t*\tvalid:\t\t./main --w=sine --f=16.5\n");
    printf("\t\t*\tinvalid:\t./main --fp --f=16.5\n\t\t*\tinvalid:\t./main --w=sine --w=rectangle\n");
}

void Error_InvalidArgument() {
    fprintf(stderr, "Invalid program arguments!\n");
    fprintf(stderr, "Check whether there exists any incomplete, duplicate, or incompatible declaration.\n");
    fprintf(stderr, "Use --h to view program argument instructions.\n");
}

void Error_InvalidValue() {
    fprintf(stderr, "Invalid parameter value exists!\n");
    fprintf(stderr, "Use --h to view program argument instructions.\n");
}

void Warning_ValueExceededLimit() {
    printf("Value exceeded limit! Continuing with the allowed maximum value.\n");
}

void Error_CannotOpenFile() {
    perror("Cannot open the file specified");
}

void Error_WrongFileData() {
    fprintf(stderr, "Something wrong with the file data!\n");
    fprintf(stderr, "Use --h to view file data instructions.\n");
}

void WaveInitializationComplete() {
    printf("Wave initialization finished.\n");
    printf("____________________________\n");
    printf("\tWaveform:\t");
    switch (wave.waveform) {
        case Sine:
            printf("Sine\n");
            break;
        case Rectangle:
            printf("Rectangle\n");
            break;
        case Triangle:
            printf("Triangle\n");
            break;
        case Sawtooth:
            printf("Sawtooth\n");
            break;
    }
    printf("\tAmplitude:\t%.2lf\n", wave.amplitude);
    printf("\tFrequency:\t%.2lf\n", wave.frequency);
    printf("____________________________\n");
}

void Error_CannotCreateTimer() {
    fprintf(stderr, "Failed to create a timer!\n");
}

void Error_CannotSetTimer() {
    fprintf(stderr, "Failed to set the timer!\n");
}
