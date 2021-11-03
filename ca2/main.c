#include <stdio.h>

#include "datatypes/struct.h"
#include "functions/initialization.h"
#include "functions/wave_generator_pcie.h"
#include "functions/pcie_control.h"

#define USING_LAB_PC 0

#if USING_LAB_PC
#include <hw/pci.h>
#endif

int main(int argc, char **argv)
{
    void *hdl;
    struct Wave wave;
    uintptr_t iobase[6];

    WaveInitialization(&wave, argc, argv);
//    PCIeInitialization(&hdl, &iobase);
    GenerateWave(&wave);

    printf("Program ended.\n");
    //pci_detach_device(hdl);
    return 0;
}