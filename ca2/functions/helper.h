#ifndef HELPER
#define HELPER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *SliceString(char *ori_str, int start_index) {
    unsigned int i;
    char *sliced_str;

    if(strlen(ori_str)-1 < start_index) {
        fprintf(stderr, "SliceString: Start position is greater than the string length!\n");
        exit(1);
    }

    if ((sliced_str = (char *) malloc(100 * sizeof(char))) == NULL) {
        perror("SliceString: Not enough memory!\n");
        exit(1);
    }
    for (i = 0; i < strlen(ori_str) - start_index; i++) {
        sliced_str[i] = ori_str[i + start_index];
    }
    free((void*)sliced_str);

    return sliced_str;
}

bool IsFloat(char *str) {
    int len, ret;
    float ignore;

    ret = sscanf(str, "%f %n", &ignore, &len);

    return ret==1 && !str[len];
}

#endif HELPER