#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#include <ncurses.h>

#include "../datatypes/struct.h"
#include "logging.h"
#include "pcie_control.h"
#include "input.h"
#include "../main.h"

void *ReadSwitch(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        dio_switch = in8(DIO_Data);     // read switch
        out8(DIO_Data, dio_switch);     // update LED light
        switch (dio_switch) {
            case 1:
                wave.waveform = Sine;
                break;
            case 2:
                wave.waveform = Rectangle;
                break;
            case 4:
                wave.waveform = Triangle;
                break;
            case 8:
                wave.waveform = Sawtooth;
                break;
            default:
                wave.waveform = Empty;
                break;
        }
        pthread_mutex_unlock(&mutex);
        delay(1);
    }
}

void *ReadPot(void *arg) {
    double dummy;
    unsigned int prev_adc0, prev_adc1;
    double amp_max = 2.5, amp_min = 0, duty_cycle_max = 100, duty_cycle_min = 0;

    while (1) {
        pthread_mutex_lock(&mutex);
        out16(ADC_Data, 0);        // Initiate Read #0
        delay(1);
        while (in8(ADC_Stat2) > 0x80);
        adc_in[0] = in16(ADC_Data);

        out16(ADC_Data, 0);        // Initiate Read #1
        delay(1);
        while (in8(ADC_Stat2) > 0x80);
        adc_in[1] = in16(ADC_Data);

        if (abs(prev_adc0 - adc_in[0]) > 30) {
            // not noise
            dummy = (adc_in[0] / (float) 65525) * amp_max;
            if (dummy > amp_max) {
                dummy = amp_max;
            } else if (dummy < amp_min) {
                dummy = amp_min;
            }
            wave.amplitude = dummy;
        }

        if (abs(prev_adc1 - adc_in[1]) > 30) {
            // not noise
            dummy = (adc_in[1] / (float) 65525) * duty_cycle_max;
            if (dummy > duty_cycle_max) {
                dummy = duty_cycle_max;
            } else if (dummy < duty_cycle_min) {
                dummy = duty_cycle_min;
            }
            wave.duty_cycle = dummy;
        }

        prev_adc0 = adc_in[0];
        prev_adc1 = adc_in[1];
        pthread_mutex_unlock(&mutex);
        delay(1);
    }
}

void *ReadArrowKey(void *arg) {
    int input;
    double freq_max = 300, freq_min = 1;

    while (1) {
        input = getch();
        switch (input) {
            case KEY_UP:
                if (wave.frequency < freq_max) {
                    wave.frequency += 0.1;
                } else {
                    wave.frequency = freq_max;
                }
                break;
            case KEY_DOWN:
                if (freq_min < wave.frequency) {
                    wave.frequency -= 0.1;
                } else {
                    wave.frequency = freq_min;
                }
                break;
            default:
                break;
        }
    }
}

