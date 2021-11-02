#include <stdio.h>
#include "struct.h"

void GenerateWave(struct Wave *wave){
    switch (wave->waveform)
    {
        case Sine:
            printf("Sine\n");
//            GenerateSineWave(wave->amplitude, wave->frequency);
            break;
        case Rectangle:
            printf("Rectangle\n");
            break;
        case Triangle:
            printf("Triangle\n");
            break;
        case Sawtooth:
            printf("Sawtooth\n");
            break;
        default:
            break;
    }
}