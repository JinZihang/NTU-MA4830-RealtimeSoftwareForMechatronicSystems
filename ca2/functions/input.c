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
#include "print.h"
#include "input.h"
#include "pcie_control.h"
#include "../main.h"
#include "logging.h"

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
        /*
        if (dio_switch != switch0_prev) {
            //DEBOUNCING
            delay(1);
            //read SWITCH0 again
            dio_switch = in8(DIO_Data);
            if (switch0_value(dio_switch) == switch0)
            {
                //change detected from 0 to 1
                if (switch0 == 0)    //0=keyboard input
                {

                    //input from keyboard
                    input_mode = 0;

                    delay(1000);

                    //kill hardware_input thread, spawn keyboard_input thread

                    pthread_create(&keyboard_input_thread_ID, NULL, &keyboard_input_thread,
                                   NULL);   //keyboard_input_thread

                }
                    //change detected from 1 to 0
                else if (switch0 == 1)    //1=hardware input
                {
                    //input from hardware
                    input_mode = 1;

                    delay(1000);

                    //keyboard_input thread terminates itself, spawn hardware_input thread
                    pthread_cancel(keyboard_input_thread_ID);
                    pthread_create(&hardware_input_thread_ID, NULL, &hardware_input_thread,
                                   NULL);   //hardware_input_thread
                }
                //update switch0_prev
                switch0_prev = switch0;

            }
        }
        */
    }
}

void *ReadPot(void *arg) {
    double dummy;
    unsigned int prev_adc0, prev_adc1;
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
            dummy = (adc_in[0] / (float) 65525) * 2.5;
            if (dummy > 2.5) {
                Warning_ValueExceededLimit();
                dummy = 2.5;
            }
            wave.amplitude = dummy;
        }

        if (abs(prev_adc1 - adc_in[1]) > 30) {
            // not noise
            dummy = (adc_in[1] / (float) 65525) * 100;
            if (dummy > 100) {
                Warning_ValueExceededLimit();
                dummy = 100;
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
    int frequencyMin = 1;
    int frequencyMax = 300;

    while (1) {
        input = wgetch(win);
        switch (input) {
            case KEY_UP:
                if (wave.frequency < frequencyMax) {
                    wave.frequency = wave.frequency + 0.1;
                } else {
                    Warning_ValueExceededLimit();
                }
                break;
            case KEY_DOWN:
                if (frequencyMin < wave.frequency) {
                    wave.frequency = wave.frequency - 0.1;
                } else {
                    Warning_ValueExceededLimit();
                }
                break;
            default:
                break;
        }
    }
}

