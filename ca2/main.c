#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "main.h"
#include "datatypes/struct.h"
#include "functions/print.h"
#include "functions/helper.h"
#include "functions/initialization.h"
#include "functions/pcie_control.h"
#include "functions/wave_generator_pcie.h"
#include "functions/input.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct Wave wave;

time_t timerid;    
struct timespec now;      
struct itimerspec timer;  
long timesec, timeint;
int rtn;


int UpdateTimer() {
    struct itimerspec timerInfo;
    timerInfo.it_value.tv_sec = 1;
    timerInfo.it_value.tv_nsec = 0;
    timerInfo.it_interval.tv_sec = 10;
    timerInfo.it_interval.tv_nsec = 0;
    return timer_settime(timerid, 0, &timerInfo, NULL);
}


int main(int argc, char **argv) {
    int i, j, wave_count;
    FILE *fp;
    bool ran_by_file = false;
    double file_data[10][3]; // read maximum 10 rows

    // CMake path, use different path to run from different directory.
    DisplayTitle("assets/title.txt");

    wave_count = WaveInitialization(fp, argc, argv);

    PCIeInitialization();

    if (wave_count > 1) { // input is from file
        ran_by_file = true;
        wave_count--;

        if ((fp = fopen(SliceString(argv[1], 5), "r")) == NULL) {
            Error_CannotOpenFile();
            exit(1);
        }

        for (i = 0; i < wave_count; i++) {
            for (j = 0; j < 3; j++) {
                if (fscanf(fp, "%lf", &file_data[i][j]) != 1) {
                    break;
                }
            }
        }
    }

    for (i = 0; i < wave_count; i++) {
        if (ran_by_file) {
            printf("Initializing wave for file row %d...\n", i);
            if (file_data[i][0] == 0 | file_data[i][0] == 1) {
                wave.waveform = Sine;
            } else if (file_data[i][0] == 2) {
                wave.waveform = Rectangle;
            } else if (file_data[i][0] == 3) {
                wave.waveform = Triangle;
            } else if (file_data[i][0] == 4) {
                wave.waveform = Sawtooth;
            } else {
                Error_WrongFileData();
                fclose(fp);
                exit(1);
            }

            if (file_data[i][1] > 2.5) {
                wave.amplitude = 2.5;
                Warning_ValueExceededLimit();
            } else if (file_data[i][1] > 0) {
                wave.amplitude = file_data[i][1];
            } else if (file_data[i][1] == 0) {
                wave.amplitude = 10;
            } else {
                Error_WrongFileData();
                fclose(fp);
                exit(1);
            }

            if (file_data[i][2] > 300) {
                wave.frequency = 300;
                Warning_ValueExceededLimit();;
            } else if (file_data[i][2] > 0) {
                wave.frequency = file_data[i][2];
            } else if (file_data[i][2] == 0) {
                wave.frequency = 10;
            } else {
                Error_WrongFileData();
                fclose(fp);
                exit(1);
            }

            WaveInitializationComplete();
        }

        printf("Running the program...\n\n");
        // put the main body here
        
        signal(SIGALRM, alarm_handler);    //////////

        // Create the timer, binding to the event
        if (timer_create(CLOCK_REALTIME, NULL, &timerid) == -1)
        {
            printf("Error: failed to create timer\n");
            exit(-1);
        }

        timerInfo.it_value.tv_sec= 1;
        timerInfo.it_value.tv_nsec = 0;
        timerInfo.it_interval.tv_sec = 10;
        timerInfo.it_interval.tv_nsec = 0;
        rtn = timer_settime(timerid, 0, &timerInfo, NULL);
        if( rtn == -1 ) {
            printf( "\nError setting timer!\n" ); exit(1); }
        while(1) {
            sleep(1);
        }

        pthread_create( NULL, NULL, &ReadSwitch, NULL );
        pthread_create( NULL, NULL, &GenerateWave, NULL );
        pthread_create( NULL, NULL, &ReadArrowkey, NULL );

        while (1) {
        }
    }

    printf("Program ended.\n");
    if (ran_by_file) fclose(fp);
    return 0;
}