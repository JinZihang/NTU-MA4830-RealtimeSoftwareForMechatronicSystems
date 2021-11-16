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

typedef struct
{
    char modetemp[1024];
    int modenum;
    int frequency;
} setting;

typedef struct
{
    int min;
    int max;
} freqLimit;

int readArrow();

int readArrow()
{   
    int int_1 = 0;
    int int_2 = 0;
    int int_3 = 0;

    printf("\nPlease using up and down key to adjust the frequency you want.");
    system("/bin/stty raw");
    scanf("%d", &int_3);
    int_1 = getchar();
    if (int_1 == 27)
    {
        int_2 = getchar();
        int_3 = getchar();
    }
    system("/bin/stty edit");

    return int_3;
}

void* ReadArrowkey(void* arg)
{
    int input;
    int status = 1;

    freqLimit frequencyRange;
    frequencyRange.min = 1;
    frequencyRange.max = 300;
    wave.frequency = 50; //initialized or default 
    while (status)
    {
        input = readArrow();
        switch (input)
        {
        case 65:
            printf("\n");
            if (wave.frequency < frequencyRange.max)
            {
                wave.frequency=wave.frequency+20;
            }
            else
            {
                printf( "[WARN]   Maximum limit reached, can't add more.\n" );
            }
            break;
        case 66:
            printf("\n");
            if (frequencyRange.min < wave.frequency)
            {
                wave.frequency=wave.frequency-20;
            }
            else
            {   
                printf( "[WARN]   Minimum limit reached, can't reduce more.\n" );
            }
            break;
        case 67:
            printf("Right!\n");
            break;
        case 68:
            printf("Left!\n");
            break;
        case 'q':
            status = 0;
            break;
        default:
            status = 0;
            printf("end editing\n");
            break;
        }
        printf("The current frequency is %d.", wave.frequency);
        fflush(stdout);
    }

    return wave.frequency;
};