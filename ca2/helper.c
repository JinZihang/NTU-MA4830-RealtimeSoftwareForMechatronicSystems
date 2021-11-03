#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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