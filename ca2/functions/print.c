#include <stdio.h>
#include <stdlib.h>

#include "../datatypes/struct.h"

#define MAX_LEN 128

void DisplayImage(FILE *fptr) {
    char readString[MAX_LEN];

    while (fgets(readString, sizeof(readString), fptr) != NULL)
        printf("%s", readString);
    printf("\n");
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
    printf("\t\t--h\tshow program argument instructions\n");
    printf("\t\t--fn\trun the program based on the data from a specific file\n");
    printf("\t\t--w\tselect a waveform (sine/rectangle/triangle/sawtooth) (default is sine)\n");
    printf("\t\t--a\treplace the default wave amplitude with your own value (default is 10)\n");
    printf("\t\t--f\treplace the default wave frequency with your own value (default is 10)\n");
    printf("notes\n");
    printf("\t\t*\t--h, --fn cannot be used together with other arguments\n");
    printf("\t\t*\tincomplete or duplicate declarations are not allowed\n");
    printf("\t\t*\tamplitude and frequency arguments only accept positive numeric values\n");
    printf("examples\n");
    printf("\t\tvalid:\t\t./main --fn=../data.txt\n\t\tvalid:\t\t./main --w=sine --f=16.5\n");
    printf("\t\tinvalid:\t./main --fn --f=16.5\n\t\tinvalid:\t./main --w=sine --w=rectangle\n");
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

void WaveInitializationComplete(struct Wave *wave) {
    printf("Wave initialization finished.\n");
    printf("____________________________\n");
    printf("\tWaveform:\t");
    switch (wave->waveform) {
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
    printf("\tAmplitude:\t%.2lf\n", wave->amplitude);
    printf("\tFrequency:\t%.2lf\n", wave->frequency);
    printf("____________________________\n");
}