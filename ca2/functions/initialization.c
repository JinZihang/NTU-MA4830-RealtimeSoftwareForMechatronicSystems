#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../datatypes/struct.h"
#include "logging.h"
#include "helper.h"
#include "../main.h"

int WaveInitialization(int argc, char **argv) {
    int i, j;
    int file_r_count, file_data_reader;
    char *arg_waveform, *arg_amplitude, *arg_frequency, *arg_duty_cycle;
    bool has_waveform_arg = false, has_amplitude_arg = false, has_frequency_arg = false, has_duty_cycle_arg = false;

    if (argc > 5) Error_ProgramArguments();

    if (argc == 2) {
        if (strcmp(argv[1], "--h") == 0) {
            ArgumentInstructions();
        } else if (strncmp(argv[1], "--fp=", 5) == 0) {
            if (strlen(argv[1]) == 4) Error_ProgramArguments();
            if ((fp = fopen(SliceString(argv[1], 5), "r")) == NULL) Error_OpenFile();

            for (i = 0; i < 10; i++) {
                for (j = 0; j < 4; j++) {
                    file_data_reader = fscanf(fp, "%lf", &file_data[i][j]);
                    switch (file_data_reader) {
                        case -1:
                            break;
                        case 1:
                            file_r_count = i + 1;
                            break;
                        default:
                            Error_FileData();
                    }
                }
            }
            // to create a difference between the 1 wave from file and from parameter argument
            return file_r_count + 1;
        }
    }

    for (i = 1; i < argc; i++) {
        // Parameter argument passing mode 
        if (strncmp(argv[i], "--w=", 4) == 0) {
            if (strlen(argv[i]) == 4) Error_ProgramArguments();
            if (has_waveform_arg == true) Error_ProgramArguments();

            arg_waveform = SliceString(argv[i], 4);

            if (strcmp(arg_waveform, "sine") == 0) {
                wave.waveform = Sine;
                has_waveform_arg = true;
            } else if (strcmp(arg_waveform, "rectangle") == 0) {
                wave.waveform = Rectangle;
                has_waveform_arg = true;
            } else if (strcmp(arg_waveform, "triangle") == 0) {
                wave.waveform = Triangle;
                has_waveform_arg = true;
            } else if (strcmp(arg_waveform, "sawtooth") == 0) {
                wave.waveform = Sawtooth;
                has_waveform_arg = true;
            } else {
                Error_ArgumentValue();
            }
        } else if (strncmp(argv[i], "--a=", 4) == 0) {
            if (strlen(argv[i]) == 4) Error_ProgramArguments();
            if (has_amplitude_arg == true) Error_ProgramArguments();

            arg_amplitude = SliceString(argv[i], 4);

            if (IsFloat(arg_amplitude) & (atof(arg_amplitude) > 0)) {
                if (atof(arg_amplitude) > 2.5) {
                    wave.amplitude = 2.5;
                } else {
                    wave.amplitude = atof(arg_amplitude);
                }
                has_amplitude_arg = true;
            } else {
                Error_ArgumentValue();
            }
        } else if (strncmp(argv[i], "--f=", 4) == 0) {
            if (strlen(argv[i]) == 4) Error_ProgramArguments();
            if (has_frequency_arg == true) Error_ProgramArguments();

            arg_frequency = SliceString(argv[i], 4);

            if (IsFloat(arg_frequency) & (atof(arg_frequency) > 0)) {
                if (atof(arg_frequency) > 300) {
                    wave.frequency = 300;
                } else if (atof(arg_frequency) < 1) {
                    wave.frequency = 1;
                } else {
                    wave.frequency = atof(arg_frequency);
                }
                has_frequency_arg = true;
            } else {
                Error_ArgumentValue();
            }
        } else if (strncmp(argv[i], "--d=", 4) == 0) {
            if (strlen(argv[i]) == 4) Error_ProgramArguments();
            if (has_duty_cycle_arg == true) Error_ProgramArguments();

            arg_duty_cycle = SliceString(argv[i], 4);

            if (IsFloat(arg_duty_cycle) & (atof(arg_duty_cycle) > 0)) {
                if (atof(arg_duty_cycle) > 100) {
                    wave.duty_cycle = 100;
                } else {
                    wave.duty_cycle = atof(arg_duty_cycle);
                }
                has_duty_cycle_arg = true;
            } else {
                Error_ArgumentValue();
            }
        } else {
            Error_ProgramArguments();
        }
    }

    // auto-fill undefined configurations
    if (!has_waveform_arg) wave.waveform = Sine;
    if (!has_amplitude_arg) wave.amplitude = 1;
    if (!has_frequency_arg) wave.frequency = 1;
    if (!has_duty_cycle_arg) wave.duty_cycle = 50;

    return 1;
}

void WaveInitializationByFile(int i) {
    // Batch file passing mode 
    if (file_data[i][0] == 0 | file_data[i][0] == 1) {
        wave.waveform = Sine;
    } else if (file_data[i][0] == 2) {
        wave.waveform = Rectangle;
    } else if (file_data[i][0] == 3) {
        wave.waveform = Triangle;
    } else if (file_data[i][0] == 4) {
        wave.waveform = Sawtooth;
    } else {
        Error_FileData();
    }

    if (file_data[i][1] > 2.5) {
        wave.amplitude = 2.5;
    } else if (file_data[i][1] > 0) {
        wave.amplitude = file_data[i][1];
    } else if (file_data[i][1] == 0) {
        wave.amplitude = 1;
    } else {
        Error_FileData();
    }

    if (file_data[i][2] > 300) {
        wave.frequency = 300;
    } else if (file_data[i][2] > 0) {
        wave.frequency = file_data[i][2];
    } else if (file_data[i][2] == 0) {
        wave.frequency = 1;
    } else {
        Error_FileData();
    }

    if (file_data[i][3] > 100) {
        wave.duty_cycle = 100;
    } else if (file_data[i][3] > 0) {
        wave.duty_cycle = file_data[i][3];
    } else if (file_data[i][3] == 0) {
        wave.duty_cycle = 1;
    } else {
        Error_FileData();
    }
}
