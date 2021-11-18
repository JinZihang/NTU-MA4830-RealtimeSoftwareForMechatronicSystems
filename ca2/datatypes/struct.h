#ifndef METRONOME_STRUCT_H
#define METRONOME_STRUCT_H

#include "enum.h"

struct Wave {
    enum Waveform waveform;
    double amplitude;
    double frequency;
};

#endif
