#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "input.h"
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

void *ReadSwitch(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        dio_switch = in8(DIO_Data);    // read switch
        out8(DIO_Data, dio_switch); //update LED light
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
//        if (dio_switch != switch0_prev) {
//            //DEBOUNCING
//            delay(1);
//            //read SWITCH0 again
//            dio_switch = in8(DIO_Data);
//            if (switch0_value(dio_switch) == switch0)
//            {
//                //change detected from 0 to 1
//                if (switch0 == 0)    //0=keyboard input
//                {
//
//                    //input from keyboard
//                    input_mode = 0;
//
//                    delay(1000);
//
//                    //kill hardware_input thread, spawn keyboard_input thread
//
//                    pthread_create(&keyboard_input_thread_ID, NULL, &keyboard_input_thread,
//                                   NULL);   //keyboard_input_thread
//
//                }
//                    //change detected from 1 to 0
//                else if (switch0 == 1)    //1=hardware input
//                {
//                    //input from hardware
//                    input_mode = 1;
//
//                    delay(1000);
//
//                    //keyboard_input thread terminates itself, spawn hardware_input thread
//                    pthread_cancel(keyboard_input_thread_ID);
//                    pthread_create(&hardware_input_thread_ID, NULL, &hardware_input_thread,
//                                   NULL);   //hardware_input_thread
//                }
//                //update switch0_prev
//                switch0_prev = switch0;
//
//            }
//        }
    }
}

int readArrow()
{   
    // Read the up and down arrow key to adjust frequency
    int int_1 = 0;
    int int_2 = 0;
    int int_3 = 0;

    printf("Please using up and down key to adjust the frequency you want.\n");
    system("/bin/stty raw");
    scanf("%d", &int_3);
    int_1 = getchar();
    if (int_1 == 27)
    {
        int_2 = getchar();
        int_3 = getchar();
        printf("\r          ");
    }
    system("/bin/stty cooked");

    return int_3;
}

//typedef struct
//{
//    int min;
//    int max;
//} freqLimit;
//
//freqLimit frequencyRange;
//frequencyRange.min = 0;
//frequencyRange.max = 300;

void* ReadArrowkey(void* arg){
    int input;
    int status = 1;
    int frequencyMax = 300;
    int frequencyMin = 0;

    while (1) {
        pthread_mutex_lock(&mutex);
        input = readArrow();
        switch (input) {
            case 65:
                printf("\n");
                if (wave.frequency + 20 < frequencyMax) {
                    wave.frequency = wave.frequency + 20;
                    // if (UpdateTimer(.........) {        //signal handler
                    // printf( "\n[ERROR] Fail to set timer!\n" );
                    // TerminateProgram();}
                } else {
                    printf("[WARN]   Maximum limit reached, can't add more.\n");
                }
                break;
            case 66:
                printf("\n");
                if (frequencyMin < wave.frequency - 20) {
                    wave.frequency = wave.frequency - 20;
                    // if (UpdateTimer(..........) {       //signal handler
                    // printf(KRED "\n[ERROR] Fail to set timer!\n" KNRM);
                    // TerminateProgram();}
                } else {
                    printf("[WARN]   Minimum limit reached, can't reduce more.\n");
                }
                break;
            case 67:
                printf("Right Arrow key!\n");
                break;
            case 68:
                printf("Left Arrow key!\n");
                break;
            case 'q':
                status = 0;
                break;
            default:
                status = 0;
                printf("end editing\n");
                break;

                printf("The current frequency is %d.\n", wave.frequency);

        }
    }
}

void* ReadPot(void* arg)
{
    double dummy;
    while (1) {
        pthread_mutex_lock(&mutex);
        out16(ADC_Data,0);		// Initiate Read #0
        delay(1);
        while(in8(ADC_Stat2) >0x80);
        adc_in[0]=in16(ADC_Data);

        out16(ADC_Data,0);		// Initiate Read #1
        delay(1);
        while(in8(ADC_Stat2) >0x80);
        adc_in[1]=in16(ADC_Data);

        printf("Chan#0 : %04x Chan#1 : %04x\n",adc_in[0],adc_in[1]);

        dummy = (adc_in[0] / (float) 65525) * 2.5;
        if (dummy > 2.5)
        {
            dummy = 2.5;
        }
        wave.amplitude = dummy;

        pthread_mutex_unlock(&mutex);
        delay(1);
    }
}