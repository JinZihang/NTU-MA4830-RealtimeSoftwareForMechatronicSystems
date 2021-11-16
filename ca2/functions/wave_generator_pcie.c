#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define _USE_MATH_DEFINES

#include <math.h>
#include "../datatypes/struct.h"
#include "wave_generator_pcie.h"
#include "pcie_control.h"
#include "../main.h"

#define USING_LAB_PC 1
#if USING_LAB_PC
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#endif

//******************************************************************************
// D/A Port Functions
// Set to 5V, Unipolar 16 bit offset map. 0V->0x0000 mid >0x7fff 5V->0xffff
// PCIe: 12 bit
//******************************************************************************

void GenerateSineWave() {
    double dummy, delta;
    double prev_amp;

    printf("Generating sine wave.\n");

    delta = 1/(100 * wave.frequency);
    for (i = 0; i < 100; i++) {
        dummy = (((sinf((float)((i * 2 * M_PI) / 100))) * wave.amplitude) + wave.amplitude) * (0xFFFF/5);
//        dummy = ((sinf((float) (i * 2 * M_PI / 100))) + 1.0) * 0x0800;
        data[i] = (unsigned) dummy;
        printf("%f\n", dummy);
    }

    while (wave.waveform == Sine && wave.amplitude == prev_amp) {
        for (j = 0; j < 100; j++) {
            out16(DAC0_Data, data[j]);
            delay(delta * 1000);
        }
        prev_amp = wave.amplitude;
    }

    printf("Sine wave output ended.\n");
}

void GenerateRectangleWave() {
    double dummy, delta;
    double prev_amp;
    printf("Generating rectangle wave.\n");

    delta = 1/(100 * wave.frequency);
    for (i = 0; i < 100; i++) {
        dummy = ((i < 50) ? 0 : 2 * wave.amplitude) * (0xFFFF/5);
        data[i] = (unsigned) dummy;
        printf("%f\n", dummy);
    }

    while (wave.waveform == Rectangle && wave.amplitude == prev_amp) {
        for (j = 0; j < 100; j++) {
            out16(DAC0_Data, data[j]);
            delay(delta * 1000);
        }
        prev_amp = wave.amplitude;
    }
//
//    while (wave.waveform == Rectangle) {
//        for (j = 0x0000; j < 0x0fff; j++) {
//            out16(DAC0_Data, ((j > 0x0800) ? 0 : 0x0fff));
//            printf("Output to DAC0_Data: %x\n", ((j > 0x0800) ? 0 : 0x0fff));
//        }
//    }

    printf("Rectangle wave output ended.\n");
}

void GenerateSawtoothWave() {
    double dummy, delta;
    double prev_amp;
    printf("Generating sawtooth wave.\n");

//    delta = 1/(100 * wave.frequency);
//    for (i = 0; i < 100; i++) {
//        dummy = ((i < 50) ? 0 : 2 * wave.amplitude) * (0xFFFF/5);
//        data[i] = (unsigned) dummy;
//        printf("%f\n", dummy);
//    }
//
//    while (wave.waveform == Sawtooth && wave.amplitude == prev_amp) {
//        for (j = 0; j < 100; j++) {
//            out16(DAC0_Data, data[j]);
//            delay(delta * 1000);
//        }
//        prev_amp = wave.amplitude;
//    }

    while (wave.waveform == Sawtooth) {
        for (j = 0x0000; j < 0x0fff; j++) {
            out16(DAC0_Data, (j & 0x0fff));
            printf("Output to DAC0_Data: %x\n", (j & 0x0fff));
        }
    }

    printf("Sawtooth wave output ended.\n");
}

void GenerateTriangleWave() {
    bool slope_dir = true;

    printf("Generating triangle wave.\n");

    while (wave.waveform == Triangle) {
        for (j = 0x0000; j < 0x0fff; j++) {
            out16(DAC0_Data, slope_dir ? (j & 0x0fff) : 0x0fff - (j & 0x0fff));
            printf("Output to DAC0_Data: %x\n", slope_dir ? (j & 0x0fff) : 0x0fff - (j & 0x0fff));
        }
        slope_dir = !slope_dir;
    }

    printf("Triangle wave output ended.\n");
}

void GenerateEmptyWave()
{
    while (wave.waveform == Empty)
    {
        out16(DAC0_Data, 0x000);
    }
}

void* GenerateWave() {
    while(1)
    {
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
                GenerateTriangleWave();
                break;
            case Sawtooth:
                printf("Sawtooth\n");
                GenerateSawtoothWave();
                break;
            default:
                printf("Empty");
                GenerateEmptyWave();
                break;
        }
        delay(1);
    }
    return 0;
}