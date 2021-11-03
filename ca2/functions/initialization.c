#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../datatypes/struct.h"
#include "helper.h"

void WaveInitialization(struct Wave *wave, int argc, char **argv)
{
    unsigned int i;
    char *arg_waveform, *arg_amplitude, *arg_frequency;
    bool has_waveform_arg = false, has_amplitude_arg = false, has_frequency_arg = false;

    if (argc > 4) {
        fprintf(stderr, "Too many arguments!\n");
        exit(1);
    }

    for (i = 1; i < argc; i++) {
        if (strncmp(argv[i], "waveform=", 9) == 0) {
            if (strlen(argv[i]) == 9) {
                fprintf(stderr, "Empty declaration not allowed!\n");
                exit(1);
            }

            if (has_waveform_arg == true) {
                fprintf(stderr, "Duplicate waveform input!\n");
                exit(1);
            }

            arg_waveform = SliceString(argv[i], 9);

//            printf("after slice: %s\n", arg_waveform);

            if (strcmp(arg_waveform, "sine") == 0) {
                wave->waveform = Sine;
                has_waveform_arg = true;
            } else if (strcmp(arg_waveform, "rectangle") == 0) {
                wave->waveform = Rectangle;
                has_waveform_arg = true;
            } else if (strcmp(arg_waveform, "triangle") == 0) {
                wave->waveform = Triangle;
                has_waveform_arg = true;
            } else if (strcmp(arg_waveform, "sawtooth") == 0) {
                wave->waveform = Sawtooth;
                has_waveform_arg = true;
            } else {
                fprintf(stderr, "Wrong waveform parameter\n");
                exit(1);
            }
        } else if (strncmp(argv[i], "amplitude=", 10) == 0) {
            if (strlen(argv[i]) == 10) {
                fprintf(stderr, "Empty declaration not allowed!\n");
                exit(1);
            }

            if (has_amplitude_arg == true) {
                fprintf(stderr, "Duplicate amplitude input!\n");
                exit(1);
            }

            arg_amplitude = SliceString(argv[i], 10);

            if (IsFloat(arg_amplitude)) {
                wave->amplitude = atof(arg_amplitude);
                has_amplitude_arg = true;
            }
        } else if (strncmp(argv[i], "frequency=", 10) == 0) {
            if (strlen(argv[i]) == 10) {
                fprintf(stderr, "Empty frequency not allowed!\n");
                exit(1);
            }

            if (has_frequency_arg == true) {
                fprintf(stderr, "Duplicate frequency input!\n");
                exit(1);
            }

            arg_frequency = SliceString(argv[i], 10);

            if (IsFloat(arg_frequency)) {
                wave->frequency = atof(arg_frequency);
                has_frequency_arg = true;
            }
        } else {
            fprintf(stderr, "Unexpected or incomplete argument exists!\n");
            exit(1);
        }
    }
    return;
}