#ifndef METRONOME_LOGGING_H
#define METRONOME_LOGGING_H

void NcursesInitialization();

void *UpdateDisplay();

void ClearLoggingLine();

void Error_SetTimer();

void Error_CannotCreateTimer();

void Error_WrongFileData();

void Error_CannotOpenFile();

void Warning_ValueExceededLimit();

void Info_ProgramTerminated();

void Error_InvalidArguments();

#endif
