#ifndef WAVE_GENERATOR_PCIE
#define WAVE_GENERATOR_PCIE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "../datatypes/struct.h"

#define USING_LAB_PC 0
#if USING_LAB_PC
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#endif

// Define registers for PCIe-DAS1602
#define    INTERRUPT    iobase[1] + 4       // Badr1 + 4 - PCIe 32-bit
#define    ADC_Data     iobase[2] + 0       // Badr2 + 0 - PCIe 16-bit w->srt
#define    DAC0_Data    iobase[2] + 2       // Badr2 + 2 - PCIe 12-bit
#define    DAC1_Data    iobase[2] + 4       // Badr2 + 4 - PCIe 12-bit
#define    MUXCHAN      iobase[3] + 0       // Badr3 + 0 - Mux scan/upper lower
#define    DIO_Data     iobase[3] + 1       // Badr3 + 1 - 8bit DI3 DI2 DI1 DI0
#define    ADC_Stat1    iobase[3] + 2       // Badr3 + 2 - 1 : MSB
#define    ADC_Stat2    iobase[3] + 3       // Badr3 + 3 - Alt EOC
#define    CLK_Pace     iobase[3] + 5       // Badr3 + 5 - S/W Pacer : XXXX XX0X
#define    ADC_Enable   iobase[3] + 6       // Badr3 + 6 - Brst_off Conv_EN:0x01
#define    ADC_Gain     iobase[3] + 7       // Badr3 + 7 - unipolar 5V : 0x01

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
        dummy = ((amplitude * sinf((float) (omega * i))) + amplitude);
        // dummy = ((sinf((float) (i * omega))) + 1.0) * 0x0800;
        // data[i] = (unsigned) dummy;
        printf("%f\n", dummy);
    }

    // for (i = 0; i < 100; i++) {
    //     for (j = 0; j < 100; j++) {
    //         #if USING_LAB_PC
    //         out16(DAC0_Data, data[j]);
    //         #else
    //         printf("Output to DAC0_Data: %d\n", data[j]);
    //         #endif
    //     }
    // }

    printf("Sine wave output ended.\n");
}

void GenerateRectangleWave() {
    unsigned int i, j;

    printf("Generating rectangle wave.\n");

    for (i = 0; i < 0xfffffff; i++) {
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

    for (i = 0; i < 0xfffffff; i++) {
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

    for (i = 0; i < 0xfffffff; i++) {
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

void GenerateWave(struct wave *wave) {
    switch (wave->waveform) {
        case Sine:
            printf("Sine\n");
            GenerateSineWave(wave->amplitude, wave->frequency);
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

#endif