#include "pcie_control.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>

void PCIeInitialization() {
    memset(&info, 0, sizeof(info));
    if (pci_attach(0) < 0) exit(EXIT_FAILURE);

    info.VendorId = 0x1307;
    info.DeviceId = 0x115;

    if ((hdl = pci_attach_device(0, PCI_SHARE | PCI_INIT_ALL, 0, &info)) == 0) exit(EXIT_FAILURE);

    // Assign BADRn IO addresses for PCIe-DAS1602
    for (i = 0; i < 5; i++) {
        badr[i] = PCI_IO_ADDR(info.CpuBaseAddress[i]);
    }

    // map I/O base address to user space
    for (i = 0; i < 5; i++) {
        iobase[i] = mmap_device_io(0x0f, badr[i]);
    }

    // Modify thread control privity.
    if (ThreadCtl(_NTO_TCTL_IO, 0) == -1) {
        exit(1);
    }
}

void DIOInitialization() {
    out8(CLK_Pace, 0x00);           // set to SW pacing & verify
    stat1 = in32(INTERRUPT);
    stat2 = in8(CLK_Pace);

    out8(ADC_Enable, 0x01);         // set bursting off, conversions on
    out8(ADC_Gain, 0x01);           // set range : 5V
    out8(MUXCHAN, 0x10);            // set mux for single channel scan : 1
}
