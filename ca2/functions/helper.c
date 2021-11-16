#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <hw/inout.h>
#include <sys/neutrino.h>

char *SliceString(char *ori_str, int start_index) {
    if (strlen(ori_str) - 1 < start_index) {
        fprintf(stderr, "SliceString: Start position is greater than the string length!\n");
        exit(1);
    }

    return ori_str + start_index;
}

bool IsFloat(char *str) {
    int len, ret;
    float ignore;

    ret = sscanf(str, "%f %n", &ignore, &len);

    return ret == 1 && !str[len];
}

void SoundGenerator(double amplitude) {
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
    out8(ctr + 2, amplitude * (245 - 5) / 2.5 + 5);

    delay(75);

    system_control = in8(kbd + 1);
    out8(kbd + 1, system_control & 0xfc);
}
