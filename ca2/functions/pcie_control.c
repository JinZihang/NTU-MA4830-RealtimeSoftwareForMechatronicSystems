#include "pcie_control.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>

void PCIeInitialization() {
    printf("\fInitializing PCIe-DAS1602.\n");

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
}

void DIOInitialization() {
    out8(CLK_Pace, 0x00);        // set to SW pacing & verify
    stat1 = in32(INTERRUPT);
    stat2 = in8(CLK_Pace);
    printf("Interrupt Regs : %08x ADC Regs %02x\n", stat1, stat2);

    out8(ADC_Enable, 0x01);        // set bursting off, conversions on
    out8(ADC_Gain, 0x01);        // set range : 5V
    out8(MUXCHAN, 0x10);        // set mux for single channel scan : 1
}
