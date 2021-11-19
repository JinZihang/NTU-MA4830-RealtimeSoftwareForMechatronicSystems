//******************************************************************************
// Initialization Functions
// WaveInitialization: Initialize wave struct based on different execution mode
// WaveInitialization: Initialize wave struct based on batch file execution mode
//******************************************************************************

#ifndef METRONOME_INITIALIZATION_H
#define METRONOME_INITIALIZATION_H

int WaveInitialization(int argc, char **argv);

void WaveInitializationByFile(int wave_index);

#endif
