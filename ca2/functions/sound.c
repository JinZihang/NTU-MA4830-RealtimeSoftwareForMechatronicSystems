#include <stdlib.h>
#include <unistd.h>
#include <hw/inout.h>
#include <sys/neutrino.h>

void* SoundGenerator(void* amplitude) {
    int i, kbd, ctr, system_control = 0;

    ThreadCtl(_NTO_TCTL_IO, 0);

    kbd = mmap_device_io(4, 0x60);
    ctr = mmap_device_io(4, 0x40);

    system_control = in8(kbd + 1);
    out8(kbd + 1, system_control | 0x03);

    // load control word of 8254
    out8(ctr + 3, 0xb7);

    // divide 8254 clock (1.1892 MHz) by 2702 to get 440Hz tone
    out8(ctr + 2, 0);
    out8(ctr + 2, *((double *) amplitude) * (245 - 5) / 2.5 + 5);

    delay(75);

    system_control = in8(kbd + 1);
    out8(kbd + 1, system_control & 0xfc);
}
