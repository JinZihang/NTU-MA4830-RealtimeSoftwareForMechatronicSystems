#ifndef METRONOME_MAIN_H
#define METRONOME_MAIN_H

#include <pthread.h>
#include "datatypes/struct.h"

extern struct Wave wave;
extern pthread_mutex_t mutex;

void signal_handler( int signum );

#endif //METRONOME_MAIN_H

