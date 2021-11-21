//*********************************************************************************************
//  pipe.c - Demonstrates the pipe functionality
//
//  This program creates a pipe, then forks. The child communicates to the parent over the 
//  pipe. Notice that a pipe is a one-way communications device. write to the output socket 
//  (sockets[1], the second socket of the array returned by  pipe()) and  read from the input 
//  socket (sockets[0]), but not vice versa. 
// 
//  Functions demonstrated include: fork, pipe, open, read, write
//  Note : "pipe" utility needs to run under root.
//  
//  Procedure:
//		cd .. ----> move to the upper folder 
//		compile and run
//*********************************************************************************************

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    int sockets[2], child;

    // create a pipe
    if (pipe(sockets) < 0) {
        perror("opening stream socket pair");
        exit(10);
    }

    if ((child = fork()) == -1) perror("fork");
    else if (child) {       // this is the parent, it reads the child's message
        char buf[1024];

        printf("parent-child: %d\n", child);

        close(sockets[1]);  // parent reads, child writes
        while (1) {
            if (read(sockets[0], buf, sizeof(buf)) < 0) perror("reading message");
            printf("Parent: %s\n", buf);
        }
        close(sockets[0]);
    } else {                // This is the child, it writes a message to its parent.
        int count = 0;
        char data[35];

        printf("child-child: %d\n", child);

        close(sockets[0]);
        while (1) {
            sprintf(data, "It is getting interesting: %4d\n", count);
            if (write(sockets[1], data, sizeof(data)) < 0) perror("writing message");
            ++count;
            sleep(5);
//            delay(500);
        }
        close(sockets[1]);
    }
}