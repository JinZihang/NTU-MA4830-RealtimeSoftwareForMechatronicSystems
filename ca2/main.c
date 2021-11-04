#include <stdio.h>

#include "datatypes/struct.h"
#include "functions/print.h"
#include "functions/initialization.h"

int main(int argc, char **argv) {
    int i, wave_count;
    FILE *fp;
    struct Wave wave;

    // CMake path, use different path to run from different directory.
    DisplayTitle("../assets/title.txt");

    wave_count = WaveInitialization(fp, &wave, argc, argv);

    for (i=0; i<wave_count; i++) {
        if (wave_count != 1) {
            printf("Initializing wave for row %d...\n", i);
            // initialize the wave for the ith row
            // WIP by Zihang
        }
        printf("Running the program...\n");
        // run the program
    }

    printf("Program ended.\n");
    fclose(fp);
    return 0;
}