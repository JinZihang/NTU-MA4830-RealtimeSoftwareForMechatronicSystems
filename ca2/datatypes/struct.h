#ifndef STRUCT
#define STRUCT

#include "enum.h"

struct wave
{
    double frequency;
    double amplitude;
    enum waveform waveform;
};

#endif