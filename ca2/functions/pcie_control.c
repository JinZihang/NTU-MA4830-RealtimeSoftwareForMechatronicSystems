#include <stdio.h>
#include <stdlib.h>

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

void PCIeInitialization(void *hdl)
{
#if USING_LAB_PC
    int badr[5];        // PCI 2.2 assigns 6 IO base addresses
    struct pci_dev_info info;
    int i;

    printf("\fInitializing PCIe-DAS1602.\n");

    memset(&info, 0, sizeof(info));
    if (pci_attach(0) < 0)
    {
        perror("pci_attach");
        exit(EXIT_FAILURE);
    }

    info.VendorId = 0x1307;
    info.DeviceId = 0x115;

    if ((*hdl = pci_attach_device(0, PCI_SHARE | PCI_INIT_ALL, 0, &info)) == 0) {
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

    // Assign BADRn IO addresses for PCIe-DAS1602
    printf("\nDAS 1602 Base addresses:\n\n");
    for (i = 0; i < 5; i++) {
        badr[i] = PCI_IO_ADDR(info.CpuBaseAddress[i]);
        printf("Badr[%d] : %x\n", i, badr[i]);
    }

    printf("\nReconfirm Iobase:\n");// map I/O base address to user space

    for (i = 0; i < 5; i++) {    // expect CpuBaseAddress to be the same as iobase for PC
        iobase[i] = mmap_device_io(0x0f, badr[i]);
        printf("Index %d : Address : %x ", i, badr[i]);
        printf("IOBASE  : %x \n", iobase[i]);
    }

    // Modify thread control privity.
    if (ThreadCtl(_NTO_TCTL_IO, 0) == -1) {
        perror("ThreadCtl");
        exit(1);
    }

    printf("Initialization completed.");
#else
    printf("Not attached to PCIe\n");
    exit(1);
#endif
}