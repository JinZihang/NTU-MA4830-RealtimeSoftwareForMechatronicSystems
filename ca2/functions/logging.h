#ifndef METRONOME_LOGGING_H
#define METRONOME_LOGGING_H

void NcursesInitialization();

void *UpdateDisplay();

void ClearLoggingLine();

void Error_SetTimer();

void Error_CannotCreateTimer();

void Error_WrongFileData();

void Error_CannotOpenFile();

#endif
