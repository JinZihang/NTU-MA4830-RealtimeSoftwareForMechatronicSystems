#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 128

void DisplayImage(FILE *fptr) {
    char readString[MAX_LEN];

    while (fgets(readString, sizeof(readString), fptr) != NULL)
        printf("%s", readString);
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
    printf("\t\t--h\tshow instructions of program arguments\n");
    printf("\t\t--f\tplay a file (only support .txt)\n");
    printf("\t\t--w\tselect a waveform (sine/rectangle/triangle/sawtooth) (default is sine)\n");
    printf("\t\t--a\treplace the default wave amplitude with your own value (default is 10)\n");
    printf("\t\t--f\treplace the default wave frequency with your own value (default is 10)\n");
    printf("note\n");
    printf("\t\t--h, --f cannot be used together with other arguments\n");
    printf("\t\tincomplete or duplicate declarations are not allowed\n");
    printf("\t\tamplitude and frequency only accept positive numeric values\n");
    printf("example\n");
    printf("\t\tvalid: ./main --f=data.txt\n\t\tvalid: ./main --w=sine --frequency=16.5\n");
    printf("\t\tinvalid: ./main --h --f\n\t\tinvalid: ./main --f=data.txt --w=triangle\n");
    printf("\t\tinvalid: ./main --w=sine --w=rectangle\n\t\tinvalid: ./main --f=\n");
}

void Error_UnexpectedOrIncompleteDeclaration() {
    fprintf(stderr, "Unexpected or incomplete declaration exists!\n");
    printf("Use --h to show argument instructions\n");
}

void Error_DuplicateDeclaration() {
    fprintf(stderr, "Duplicate declarations exist!\n");
    printf("Use --h to show argument instructions\n");
}

void Error_InvalidValue() {
    fprintf(stderr, "Invalid parameter value!\n");
    printf("Use --h to show argument instructions\n");
}

void WaveInitializationComplete(struct Wave *wave) {
    printf("Wave initialization finished:\n");
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