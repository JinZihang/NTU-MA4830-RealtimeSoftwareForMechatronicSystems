#include "wave_generator_pcie.h"

#include <stdio.h>
#include <pthread.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#include <ncurses.h>

#include "../datatypes/struct.h"
#include "sound.h"
#include "pcie_control.h"
#include "../main.h"
#include "logging.h"

//******************************************************************************
// D/A Port Functions
// Set to 5V, Unipolar 16 bit offset map. 0V->0x0000 mid >0x7fff 5V->0xffff
// PCIe: 12 bit
//******************************************************************************

int samples = 100;

void GenerateSineWave() {
    double dummy, delta;
    double prev_amp = wave.amplitude;

    for (i = 0; i < samples; i++) {
        dummy = (((sinf((float) ((i * 2 * M_PI) / 100))) * wave.amplitude) + wave.amplitude) * (0x0fff / (float) 5);
        data[i] = (unsigned) dummy;
    }

    while ((wave.waveform == Sine) && (fabs(wave.amplitude - prev_amp) < 0.01)) {
        prev_amp = wave.amplitude;
        delta = 1 / ((samples - 1) * wave.frequency);

        for (j = 0; j < samples; j++) {
            if (j == 24) {
                pthread_create(NULL, NULL, &SoundGenerator, &wave.amplitude);
            }

            out16(DAC0_Data, data[j]);
            delay(delta * 1000);
        }
    }
}

void GenerateRectangleWave() {
    double dummy, delta;
    double prev_amp = wave.amplitude;
    double prev_duty_cycle = wave.duty_cycle;

    for (i = 0; i < samples; i++) {
        dummy = ((i > (int) wave.duty_cycle) ? 0 : 2 * wave.amplitude) * (0x0fff / (float) 5);
        data[i] = (unsigned) dummy;
    }

    while ((wave.waveform == Rectangle) &&
            (fabs(wave.amplitude - prev_amp) < 0.01) &&
            (fabs(wave.duty_cycle - prev_duty_cycle) < 1)) {
        prev_amp = wave.amplitude;
        prev_duty_cycle = wave.duty_cycle;
        delta = 1 / ((samples - 1) * wave.frequency);
        for (j = 0; j < samples; j++) {
            if (j == 0) {
                pthread_create(NULL, NULL, &SoundGenerator, &wave.amplitude);
            }

            out16(DAC0_Data, data[j]);
            delay(delta * 1000);
        }
    }
}

void GenerateTriangleWave() {
    double dummy, delta;
    double prev_amp = wave.amplitude;

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
            if (j == 0) {
                pthread_create(NULL, NULL, &SoundGenerator, &wave.amplitude);
            }

            out16(DAC0_Data, data[j]);
            delay(delta * 1000);
        }
    }
}

void GenerateSawtoothWave() {
    double dummy, delta;
    double prev_amp = wave.amplitude;

    for (i = 0; i < samples; i++)
    {
        dummy = ((2 * wave.amplitude * i)/(float) (samples- 1)) * (0x0fff / (float) 5);
        data[i] = (unsigned) dummy;
    }

    while ((wave.waveform == Sawtooth) && (fabs(wave.amplitude - prev_amp) < 0.01)) {
        prev_amp = wave.amplitude;
        delta = 1 / ((samples - 1) * wave.frequency);
        for (j = 0; j < samples; j++) {
            if (j == 0) {
                pthread_create(NULL, NULL, &SoundGenerator, &wave.amplitude);
            }

            out16(DAC0_Data, data[j]);
            delay(delta * 1000);
        }
    }
}

void GenerateEmptyWave() {
    while (wave.waveform == Empty) {
        out16(DAC0_Data, 0x000);
    }
}

void *GenerateWave() {
    while (1) {
        switch (wave.waveform) {
            case Sine:
                GenerateSineWave();
                break;
            case Rectangle:
                GenerateRectangleWave();
                break;
            case Triangle:
                GenerateTriangleWave();
                break;
            case Sawtooth:
                GenerateSawtoothWave();
                break;
            default:
                GenerateEmptyWave();
                break;
        }
        delay(1);
    }
}