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

void* ReadSwitch(void* arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        dio_switch= in8(DIO_Data);	// read switch
        out8(DIO_Data,dio_switch); //update LED light
        switch (dio_switch)
        {
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

void* ReadArrowkey(void* arg){



}
