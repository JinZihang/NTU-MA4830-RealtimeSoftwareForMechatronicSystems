//******************************************************************************
// Ncurses Related Functions
// NcursesInitialization: Initialize ncurses window with default static attributes
// ClearLoggingLine: Clear one logs line in the logging box
// Error_SliceString: Logs an error if there is an error when slicing a string
// ArgumentInstructions: Logs help instructions for using the application
//******************************************************************************

#ifndef METRONOME_LOGGING_H
#define METRONOME_LOGGING_H

void NcursesInitialization();

void ClearLoggingLine();

void Error_SliceString();

void ArgumentInstructions();

void Error_ProgramArguments();

void Error_OpenFile();

void Error_FileData();

void Error_ArgumentValue();

void Warning_ValueExceededLimit();

void Info_ProgramTerminated();

void Error_CreateTimer();

void Error_SetTimer();

void *UpdateDisplay();

#endif
