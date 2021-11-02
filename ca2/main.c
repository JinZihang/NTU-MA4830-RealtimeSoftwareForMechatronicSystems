#include "functions/wave_generator_pcie.h"
#include "datatypes/struct.h"
#include "datatypes/enum.h"

#define USING_LAB_PC 0

int main() {
    void *hdl;

    InitializePCIe(hdl);

    printf("Program ended.\n");
    #if USING_LAB_PC
        pci_detach_device(hdl);
    #endif

    struct wave wave;
    wave.waveform = Sine;
    wave.amplitude = 1.0;

    printf("%f", wave.amplitude);

    return 0;
}