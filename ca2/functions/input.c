#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "pcie_control.h"

#define USING_LAB_PC 1
#if USING_LAB_PC
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#endif

void ReadSwitch()
{
    for (i=0;i<100;i++) {		// write out
        dio_switch= in8(DIO_Data);	// read switch
        printf("Data Read : %2x\n", dio_switch);
        delay(500);			// Pause 2 seconds
    }
}
