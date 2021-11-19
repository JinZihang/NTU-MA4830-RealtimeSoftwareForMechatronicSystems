#ifndef METRONOME_LOGGING_H
#define METRONOME_LOGGING_H

void NcursesInitialization();

void ClearLoggingLine();

void Error_SliceString();

void ArgumentInstructions();

void Error_InvalidArguments();

void Error_CannotOpenFile();

void Error_WrongFileData();g

void Error_InvalidValue();

void Warning_ValueExceededLimit();

void Info_ProgramTerminated();

void Error_CannotCreateTimer();

void Error_SetTimer();

void *UpdateDisplay();

#endif
