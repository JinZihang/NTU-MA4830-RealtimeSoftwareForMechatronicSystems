#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <process.h>

int global;

void *thread(void *arg) {
    for (;;) {
        printf("Thread process: %d\n", ++global);
        sleep(2);
    }
}

int main(int argc, char *argv[]) {
    pthread_attr_t attr;

    printf("Starting a thread from main\n");
    sleep(1);
    pthread_create(NULL, NULL, &thread, NULL);

    for (;;) {
        printf("Main process: %d\n", ++global);
        sleep(1);
    }
}

