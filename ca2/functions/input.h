//******************************************************************************
// D/A Input Functions
// ReadSwitch: Read digital input from switches
// ReadPot: Read analog input from potentiometers
// ReadArrowKey: Read digital input from keyboard arrow key
//******************************************************************************

#ifndef METRONOME_INPUT_H
#define METRONOME_INPUT_H

void *ReadSwitch(void *arg);

void *ReadPot(void *arg);

void *ReadArrowKey(void *arg);

#endif
