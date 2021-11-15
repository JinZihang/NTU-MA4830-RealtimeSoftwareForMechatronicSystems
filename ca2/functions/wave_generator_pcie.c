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

void GenerateSineWave(double amplitude, double frequency) {
    unsigned int i, j, data[100];
    double omega, dummy;

    printf("Generating sine wave.\n");

    omega = 2 * M_PI / 100;
    for (i = 0; i < 100; i++) {
//        dummy = ((amplitude * sinf((float) (omega * i))) + amplitude);
        dummy = ((sinf((float) (i * omega))) + 1.0) * 0x0800;
        data[i] = (unsigned) dummy;
        printf("%f\n", dummy);
    }

    for (i = 0; i < 1; i++) {
        for (j = 0; j < 100; j++) {
#if USING_LAB_PC
            out16(DAC0_Data, data[j]);
#else
            printf("Output to DAC0_Data: %d\n", data[j]);
#endif
        }
    }

    printf("Sine wave output ended.\n");
}

void GenerateRectangleWave() {
    unsigned int i, j;

    printf("Generating rectangle wave.\n");

    for (i = 0; i < 1; i++) {
        for (j = 0x0000; j < 0x0fff; j++) {
#if USING_LAB_PC
            out16(DAC0_Data, ((j > 0x0800) ? 0 : 0x0fff));
#else
            printf("Output to DAC0_Data: %x\n", ((j > 0x0800) ? 0 : 0x0fff));
#endif
        }
    }

    printf("Rectangle wave output ended.\n");
}

void GenerateSawtoothWave() {
    unsigned int i, j;

    printf("Generating sawtooth wave.\n");

    for (i = 0; i < 1; i++) {
        for (j = 0x0000; j < 0x0fff; j++) {
#if USING_LAB_PC
            out16(DAC0_Data, (i & 0x0fff));
#else
            printf("Output to DAC0_Data: %x\n", (i & 0x0fff));
#endif
        }
    }

    printf("Sawtooth wave output ended.\n");
}

void GenerateTriangleWave() {
    unsigned int i, j;
    bool slope_dir = true;

    printf("Generating triangle wave.\n");

    for (i = 0; i < 1; i++) {
        for (j = 0x0000; j < 0x0fff; j++) {
#if USING_LAB_PC
            out16(DAC0_Data, slope_dir ? (i & 0x0fff) : 0x0fff - (i & 0x0fff));
#else
            printf("Output to DAC0_Data: %x\n", slope_dir ? (i & 0x0fff) : 0x0fff - (i & 0x0fff));
#endif
        }
        slope_dir = !slope_dir;
    }

    printf("Triangle wave output ended.\n");
}

void GenerateEmptyWave()
{
    out16(DAC0_Data, 0x000);
}

void* GenerateWave() {
    while(1)
    {
        pthread_mutex_lock(&mutex);
        switch (wave.waveform) {
            case Sine:
                printf("Sine\n");
                GenerateSineWave(wave.amplitude, wave.frequency);
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
        pthread_mutex_unlock(&mutex);
        delay(1);
    }
    return 0;
}