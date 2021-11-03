#ifndef METRONOME_PRINT_H
#define METRONOME_PRINT_H

void DisplayImage(FILE *fptr);

void DisplayTitle(char *filename);

void ArgumentInstructions();

void Error_UnexpectedOrIncompleteDeclaration();

void Error_DuplicateDeclaration();

void Error_InvalidValue();

void WaveInitializationComplete(struct Wave *wave);

#endif
