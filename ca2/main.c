#include "functions/wave_generator_pcie.h"

#define USING_LAB_PC 0

int main() {
    void *hdl;

    InitializePCIe(hdl);

    printf("Program ended.");
    #if USING_LAB_PC
        pci_detach_device(hdl);
    #endif
    return 0;
}