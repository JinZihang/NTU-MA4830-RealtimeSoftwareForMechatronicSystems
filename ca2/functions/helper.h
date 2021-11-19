//******************************************************************************
// Helper Function to prevent code duplication
// SliceString: get a subset of a string
// IsFloat: check if a string is a float
//******************************************************************************

#ifndef METRONOME_HELPER_H
#define METRONOME_HELPER_H

char *SliceString(char *ori_str, int start_index);

bool IsFloat(char *str);

#endif
