#ifndef METRONOME_MAIN_H
#define METRONOME_MAIN_H

#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "datatypes/struct.h"

extern pthread_mutex_t mutex;
extern FILE *fp;
extern double file_data[10][3]; // read maximum 10 rows
extern struct Wave wave;
extern struct Wave previousWave;
extern timer_t timerid;
extern struct itimerspec timer;
extern int count_down;

void termination_signal_handler(int signum);

void timer_signal_handler(int signum);

#endif
