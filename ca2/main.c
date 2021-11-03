#include <stdio.h>

#include "datatypes/struct.h"
#include "functions/initialization.h"
#include "functions/wave_generator_pcie.h"

// #include <hw/pci.h>

int main(int argc, char **argv) 
{
    void *hdl;
    struct Wave wave;

     WaveInitialization(&wave, argc, argv);
    // PCIeInitialization(hdl);
     GenerateWave(&wave);

    printf("Program ended.\n");
    //pci_detach_device(hdl);
    return 0;
}