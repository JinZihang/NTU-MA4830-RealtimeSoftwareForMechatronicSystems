#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <unistd.h> // an alternative for process.h on certain OS

int main(int argc, char *argv[]) {
    pid_t pid, child_pid;
    int shmem = 999;
    int ownmem = 888;

    printf("This is the parent process : pid = %d\n\n", getpid());
    sleep(1);

    // fork creates an identical child process that also comes to this if statement
    // where child_pid is defined
    if (child_pid = fork()) {
        for (;;) {
            printf("This is the parent: child pid is %d\tshmem = %d\townmem = %d\n", child_pid, shmem, --ownmem);
            sleep(1);
        }
    } else {
        for (;;) {
            printf("This is the child: pid is %d\t\tshmem = %d\townmem = %d\n", child_pid, shmem, ++ownmem);
            sleep(1);
        }
    }

    exit(0);
}
