#ifndef __STRUCT_H
#define __STRUCT_H

#include "enum.h"

struct Wave
{
    enum waveform waveform;
    double amplitude;
    double frequency;
};

#endif