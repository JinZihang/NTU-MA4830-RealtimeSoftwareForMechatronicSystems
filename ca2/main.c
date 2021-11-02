#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "datatypes/enum.h"
#include "datatypes/struct.h"

#include "functions/initialization.h"
#include "helper.h"
#include "functions/wave_generator_pcie.h"

#define USING_LAB_PC    false

int main(int argc, char **argv) {
    void *hdl;
    struct wave wave;

    wave = WaveInitialization()
    InitializePCIe(hdl);
    GenerateWave(&wave);

    printf("Program ended.\n");
    #if USING_LAB_PC
        pci_detach_device(hdl);
    #endif
    return 0;
}