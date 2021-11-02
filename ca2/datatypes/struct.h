#ifndef STRUCT
#define STRUCT

#include "enum.h"

struct Wave
{
    enum waveform waveform;
    double amplitude;
    double frequency;
};

#endif