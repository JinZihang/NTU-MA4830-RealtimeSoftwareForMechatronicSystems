#include <stdio.h>

#include "struct.h"
#include "initialization.h"
#include "wave_generator_pcie.h"

#define USING_LAB_PC 0

#if USING_LAB_PC
#include <hw/pci.h>
#endif

int main(int argc, char **argv) 
{
    void *hdl;
    struct Wave wave;

    // int i = 0;
    // for (i = 0; i < argc; i++) {
    //     printf("argv[%d] = %s\n", i, argv[i]);
    // }

     WaveInitialization(&wave, argc, argv);
    // PCIeInitialization(hdl);
     GenerateWave(&wave);

    printf("Program ended.\n");

    #if USING_LAB_PC
        pci_detach_device(hdl);
    #endif

    return 0;
}