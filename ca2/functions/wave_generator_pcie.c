#include "wave_generator_pcie.h"

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define _USE_MATH_DEFINES

#include <math.h>
#include "../datatypes/struct.h"
#include "sound.h"
#include "pcie_control.h"
#include "../main.h"

#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>

//******************************************************************************
// D/A Port Functions
// Set to 5V, Unipolar 16 bit offset map. 0V->0x0000 mid >0x7fff 5V->0xffff
// PCIe: 12 bit
//******************************************************************************

int samples = 100;

void GenerateSineWave() {
    double dummy, delta;
    double prev_amp = wave.amplitude;

    printf("Generating sine wave.\n");

    for (i = 0; i < samples; i++) {
        dummy = (((sinf((float) ((i * 2 * M_PI) / 100))) * wave.amplitude) + wave.amplitude) * (0x0fff / (float) 5);
        data[i] = (unsigned) dummy;
    }

    while ((wave.waveform == Sine) && (fabs(wave.amplitude - prev_amp) < 0.01)) {
        prev_amp = wave.amplitude;
        delta = 1 / ((samples - 1) * wave.frequency);

        for (j = 0; j < samples; j++) {
            if (j == 24) {
                SoundGenerator(wave.amplitude);
            }

            out16(DAC0_Data, data[j]);
            delay(delta * 1000);
        }
    }

    printf("Sine wave output ended.\n");
}

void GenerateRectangleWave() {
    double dummy, delta;
    double prev_amp = wave.amplitude;
    printf("Generating rectangle wave.\n");

    for (i = 0; i < samples; i++) {
        dummy = ((i < 50) ? 0 : 2 * wave.amplitude) * (0x0fff / (float) 5);
        data[i] = (unsigned) dummy;
    }

    while ((wave.waveform == Rectangle) && (fabs(wave.amplitude - prev_amp) < 0.01)) {
        prev_amp = wave.amplitude;
        delta = 1 / ((samples - 1) * wave.frequency);
        for (j = 0; j < samples; j++) {
            if (j == 49) {
                SoundGenerator(wave.amplitude);
            }

            out16(DAC0_Data, data[j]);
            delay(delta * 1000);
        }
    }

    printf("Rectangle wave output ended.\n");
}

void GenerateTriangleWave() {
    double dummy, delta;
    double prev_amp = wave.amplitude;
    printf("Generating triangle wave.\n");

    for (i = 0; i < samples/2; i++)
    {
        dummy = ((4 * wave.amplitude * i)/(float) (samples - 1)) * (0x0fff / (float) 5);
        data[i] = (unsigned) dummy;
        data[samples - 1 - i] = (unsigned) dummy;
    }

    while ((wave.waveform == Triangle) && (fabs(wave.amplitude - prev_amp) < 0.01)) {
        prev_amp = wave.amplitude;
        delta = 1 / ((samples - 1) * wave.frequency);
        for (j = 0; j < samples; j++) {
            if (j == 49) {
                SoundGenerator(wave.amplitude);
            }

            out16(DAC0_Data, data[j]);
            delay(delta * 1000);
        }
    }

    printf("Triangle wave output ended.\n");
}

void GenerateSawtoothWave() {
    double dummy, delta;
    double prev_amp;
    printf("Generating sawtooth wave.\n");

    for (i = 0; i < samples/2; i++)
    {
        dummy = ((4 * wave.amplitude * i)/(float) (samples - 1)) * (0x0fff / (float) 5);
        data[i] = (unsigned) dummy;
        data[samples - 1 - i] = (unsigned) dummy;
    }

    while (wave.waveform == Sawtooth) {
        for (j = 0x0000; j < 0x0fff; j++) {
            if (j == 0x0ffe) {
                SoundGenerator(wave.amplitude);
            }

            out16(DAC0_Data, (j & 0x0fff));
            printf("Output to DAC0_Data: %x\n", (j & 0x0fff));
        }
    }

    printf("Sawtooth wave output ended.\n");
}

void GenerateEmptyWave() {
    printf("Generating empty wave.\n");

    while (wave.waveform == Empty) {
        out16(DAC0_Data, 0x000);
    }
}

void *GenerateWave() {
    while (1) {
        switch (wave.waveform) {
            case Sine:
                printf("Sine\n");
                GenerateSineWave();
                break;
            case Rectangle:
                printf("Rectangle\n");
                GenerateRectangleWave();
                break;
            case Triangle:
                printf("Triangle\n");
                //GenerateTriangleWave();
                break;
            case Sawtooth:
                printf("Sawtooth\n");
                //GenerateSawtoothWave();
                break;
            default:
                printf("Empty\n");
                GenerateEmptyWave();
                break;
        }
        delay(1);
    }
    return 0;
}

void *ResetTimer() {

}
