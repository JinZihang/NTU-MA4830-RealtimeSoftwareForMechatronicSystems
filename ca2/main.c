#include <stdio.h>

#include "datatypes/struct.h"
#include "functions/initialization.h"
#include "functions/wave_generator_pcie.h"

#define USING_LAB_PC 0

#if USING_LAB_PC
#include <hw/pci.h>
#endif

int main(int argc, char **argv) 
{
    void *hdl;
    struct Wave wave;

     WaveInitialization(&wave, argc, argv);
    // PCIeInitialization(hdl);
     GenerateWave(&wave);

    printf("Program ended.\n");

    #if USING_LAB_PC
        pci_detach_device(hdl);
    #endif

    return 0;
}