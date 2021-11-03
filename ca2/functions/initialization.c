#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../datatypes/struct.h"
#include "print.h"
#include "helper.h"

void WaveInitialization(struct Wave *wave, int argc, char **argv) {
    unsigned int i;
    char *arg_waveform, *arg_amplitude, *arg_frequency;
    bool has_waveform_arg = false, has_amplitude_arg = false, has_frequency_arg = false;

    if (argc > 4) {
        Error_UnexpectedOrIncompleteDeclaration();
        exit(1);
    }

    if (argc == 2) {
        if (strcmp(argv[1], "--h") == 0) {
            ArgumentInstructions();
            exit(0);
        } else if (strncmp(argv[1], "--f=", 4) == 0) {

        }
    } else {
        for (i = 1; i < argc; i++) {
            if (strncmp(argv[i], "--w=", 4) == 0) {
                if (strlen(argv[i]) == 4) {
                    Error_UnexpectedOrIncompleteDeclaration();
                    exit(1);
                }

                if (has_waveform_arg == true) {
                    Error_DuplicateDeclaration();
                    exit(1);
                }

                arg_waveform = SliceString(argv[i], 4);

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
                    Error_InvalidValue();
                    exit(1);
                }
            } else if (strncmp(argv[i], "--a=", 4) == 0) {
                if (strlen(argv[i]) == 4) {
                    Error_UnexpectedOrIncompleteDeclaration();
                    exit(1);
                }

                if (has_amplitude_arg == true) {
                    Error_DuplicateDeclaration();
                    exit(1);
                }

                arg_amplitude = SliceString(argv[i], 4);

                if (IsFloat(arg_amplitude) & atof(arg_amplitude) > 0) {
                    wave->amplitude = atof(arg_amplitude);
                    has_amplitude_arg = true;
                } else {
                    Error_InvalidValue();
                    exit(1);
                }
            } else if (strncmp(argv[i], "--f=", 4) == 0) {
                if (strlen(argv[i]) == 4) {
                    Error_UnexpectedOrIncompleteDeclaration();
                    exit(1);
                }

                if (has_frequency_arg == true) {
                    Error_DuplicateDeclaration();
                    exit(1);
                }

                arg_frequency = SliceString(argv[i], 4);

                if (IsFloat(arg_frequency) & atof(arg_frequency) > 0) {
                    wave->frequency = atof(arg_frequency);
                    has_frequency_arg = true;
                } else {
                    Error_InvalidValue();
                    exit(1);
                }
            } else {
                Error_UnexpectedOrIncompleteDeclaration();
                exit(1);
            }
        }
    }

    if (!has_waveform_arg) wave->waveform = Sine;
    if (!has_amplitude_arg) wave->amplitude = 10;
    if (!has_frequency_arg) wave->frequency = 10;


    WaveInitializationComplete(wave);
}