#include "functions/wave_generator_pcie.h"

int main() {
    void *hdl;

    InitializePCIe(hdl);

    printf("Program ended.");
    pci_detach_device(hdl);
    retrun 0;
}