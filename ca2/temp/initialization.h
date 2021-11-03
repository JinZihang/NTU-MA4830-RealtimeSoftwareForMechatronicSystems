// #ifndef INITIALIZATION
// #define INITIALIZATION

// #include <stdio.h>
// #include <string.h>
// #include <stdbool.h>

// #include "../datatypes/struct.h"

#define USING_LAB_PC 0
#if USING_LAB_PC
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#endif

// Define registers for PCIe-DAS1602
#define    INTERRUPT    iobase[1] + 4       // Badr1 + 4 - PCIe 32-bit
#define    ADC_Data     iobase[2] + 0       // Badr2 + 0 - PCIe 16-bit w->srt
#define    DAC0_Data    iobase[2] + 2       // Badr2 + 2 - PCIe 12-bit
#define    DAC1_Data    iobase[2] + 4       // Badr2 + 4 - PCIe 12-bit
#define    MUXCHAN      iobase[3] + 0       // Badr3 + 0 - Mux scan/upper lower
#define    DIO_Data     iobase[3] + 1       // Badr3 + 1 - 8bit DI3 DI2 DI1 DI0
#define    ADC_Stat1    iobase[3] + 2       // Badr3 + 2 - 1 : MSB
#define    ADC_Stat2    iobase[3] + 3       // Badr3 + 3 - Alt EOC
#define    CLK_Pace     iobase[3] + 5       // Badr3 + 5 - S/W Pacer : XXXX XX0X
#define    ADC_Enable   iobase[3] + 6       // Badr3 + 6 - Brst_off Conv_EN:0x01
#define    ADC_Gain     iobase[3] + 7       // Badr3 + 7 - unipolar 5V : 0x01

// wave WaveInitialization(int argc, char **argv) {
//     unsigned int i;
//     char *arg_waveform, *arg_amplitude, *arg_frequency;
//     bool has_waveform_arg = false, has_amplitude_arg = false, has_frequency_arg = false;
//     struct wave wave;

//     if (argc > 4) {
//         fprintf(stderr, "Too many arguments!\n");
//         exit(1);
//     }

//     for (i = 0; i < argc; i++) {
//         if (strncmp(argv[i], "waveform=", 9) == 0) {
//             if (strlen(argv[i]) == 9) {
//                 fprintf(stderr, "Empty declaration not allowed!\n");
//                 exit(1);
//             }

//             if (has_waveform_arg == true) {
//                 fprintf(stderr, "Duplicate waveform input!\n");
//                 exit(1);
//             }

//             arg_waveform = SliceString(argv[i], 9);

//             if (strcmp(arg_waveform, "sine") == 0) {
//                 wave.waveform = Sine;
//                 has_waveform_arg = true;
//             } else if (strcmp(arg_waveform, "rectangle") == 0) {
//                 wave.waveform = Rectangle;
//                 has_waveform_arg = true;
//             } else if (strcmp(arg_waveform, "triangle") == 0) {
//                 wave.waveform = Triangle;
//                 has_waveform_arg = true;
//             } else if (strcmp(arg_waveform, "sawtooth") == 0) {
//                 wave.waveform = Sawtooth;
//                 has_waveform_arg = true;
//             } else {
//                 fprintf(stderr, "Wrong waveform parameter\n");
//                 exit(1);
//             }
//         } else if (strncmp(argv[i], "amplitude=", 10) == 0) {
//             if (strlen(argv[i]) == 10) {
//                 fprintf(stderr, "Empty declaration not allowed!\n");
//                 exit(1);
//             }

//             if (has_amplitude_arg == true) {
//                 fprintf(stderr, "Duplicate amplitude input!\n");
//                 exit(1);
//             }

//             arg_amplitude = SliceString(argv[i], 10);

//             if (IsFloat(arg_amplitude)) {
//                 wave.amplitude = atof(arg_amplitude);
//                 has_amplitude_arg = true;
//             }
//         } else if (strncmp(argv[i], "frequency=", 10) == 0) {
//             if (strlen(argv[i]) == 10) {
//                 fprintf(stderr, "Empty frequency not allowed!\n");
//                 exit(1);
//             }

//             if (has_frequency_arg == true) {
//                 fprintf(stderr, "Duplicate frequency input!\n");
//                 exit(1);
//             }

//             arg_frequency = SliceString(argv[i], 10);

//             if (IsFloat(arg_frequency)) {
//                 wave.frequency = atof(arg_frequency);
//                 has_frequency_arg = true;
//             }
//         } else {
//             fprintf(stderr, "Unexpected argument exists!\n");
//             exit(1);
//         }
//     }

//     return wave;
// }

void PCIeInitialization(void *hdl) {
#if USING_LAB_PC
    struct pci_dev_info info;
#endif

    printf("\fInitializing PCIe-DAS1602.\n");

#if USING_LAB_PC
    memset(&info, 0, sizeof(info));
        if (pci_attach(0) < 0) {
            perror("pci_attach");
            exit(EXIT_FAILURE);
        }

        info.VendorId = 0x1307;
        info.DeviceId = 0x115;

        if ((hdl = pci_attach_device(0, PCI_SHARE | PCI_INIT_ALL, 0, &info)) == 0) {
            perror("pci_attach_device");
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < 6; i++) {
            if (info.BaseAddressSize[i] > 0) {
                printf("Aperture %d  Base 0x%x Length %d Type %s.\n", i,
                       PCI_IS_MEM(info.CpuBaseAddress[i]) ? (int) PCI_MEM_ADDR(info.CpuBaseAddress[i]) :
                       (int) PCI_IO_ADDR(info.CpuBaseAddress[i]), info.BaseAddressSize[i],
                       PCI_IS_MEM(info.CpuBaseAddress[i]) ? "MEM" : "IO");
            }
        }

        printf("IRQ: %d.\n", info.Irq);

        // Modify thread control privity.
        if (ThreadCtl(_NTO_TCTL_IO, 0) == -1) {
            perror("ThreadCtl");
            exit(1);
        }
#endif

    printf("Initialization completed.");
}

#endif INITIALIZATION