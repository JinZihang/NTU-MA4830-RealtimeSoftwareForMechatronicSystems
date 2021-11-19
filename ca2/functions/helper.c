#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "logging.h"

char *SliceString(char *ori_str, int start_index) {
    if (strlen(ori_str) - 1 < start_index) Error_SliceString();

    return ori_str + start_index;
}

bool IsFloat(char *str) {
    int len, ret;
    float ignore;

    ret = sscanf(str, "%f %n", &ignore, &len);

    return ret == 1 && !str[len];
}
