#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

#include "datatypes/struct.h"
#include "functions/print.h"
#include "functions/helper.h"
#include "functions/initialization.h"
#include "functions/pcie_control.h"
#include "functions/wave_generator_pcie.h"
#include "functions/input.h"
#include "functions/timer.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
FILE *fp;
double file_data[10][3]; // read maximum 10 rows
struct Wave wave;
struct Wave previousWave;

timer_t timerid;
struct itimerspec timer;
bool timer_initialized = false, count_down_finished = false;

void termination_signal_handler(int signum) {
    printf("Program terminated.\n");
    exit(0);
}

void timer_signal_handler(int signum) {
    if (timer_initialized) {
        count_down_finished = true;
    } else {
        timer_initialized = true;
    }
}

int main(int argc, char **argv) {
    int wave_index, wave_count;
    bool ran_by_file = false;

    // CMake path, use different path to run from different directory.
    DisplayTitle("assets/title.txt");

    signal(SIGINT, termination_signal_handler);
    signal(SIGALRM, timer_signal_handler);

    wave_count = WaveInitialization(argc, argv);
    PCIeInitialization();
    DIOInitialization();

    if (timer_create(CLOCK_REALTIME, NULL, &timerid) == -1) {
        Error_CannotCreateTimer();
        exit(1);
    }

    if (wave_count > 1) {
        ran_by_file = true;
        wave_count--;
    }

    for (wave_index = 0; wave_index < wave_count; wave_index++) {
        if (ran_by_file) {
            WaveInitializationByFile(wave_index);
        }

        printf("Running the program...\n\n");

        TimerInitialization();

        pthread_create(NULL, NULL, &ReadSwitch, NULL);
        pthread_create(NULL, NULL, &ReadPot, NULL);
//        pthread_create(NULL, NULL, &ReadArrowKey, NULL);
//        pthread_create(NULL, NULL, &UpdateTimer, NULL);
        pthread_create(NULL, NULL, &GenerateWave, NULL);

        while (1) {
            if (count_down_finished) break;
        }

        count_down_finished = false;
    }

    printf("Program ended.\n");
    if (ran_by_file) fclose(fp);
    timer_delete(timerid);
    return 0;
}
