#ifndef METRONOME_MAIN_H
#define METRONOME_MAIN_H

#include <stdio.h>
#include <pthread.h>

#include "datatypes/struct.h"

extern FILE *fp;
extern double file_data[10][3]; // read maximum 10 rows
extern struct Wave wave;
extern pthread_mutex_t mutex;

void signal_handler(int signum);

#endif
