//	Procedures:
//      1) open the first terminal
//		2) cc -o MSG_csrv MSG_csrv ----> compile the code first
//		3) "./MSG_csrv -s &" -----> setup server: name_attach to "myserver", MsgReceive
//		4) "./MSG_csrv -c &" -----> setup client:	name_open, Msg Send, MsgReply

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>

//*********************************************************************************************
// Server side of the code 
//*********************************************************************************************
int server() {
    name_attach_t *attach;
    char msg[30];
    int rcvid;

    // create a local name (/dev/name/local/...)
    if ((attach = name_attach(NULL, "myserver", 0)) == NULL) {
        printf("Error: failed to attach myserver\n");
        return EXIT_FAILURE;
    }

    // process MsgReceive's here now with the chid
    while (1) {
        printf("Server Waiting\n");
        rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);
        printf("The channel ID Server is %d\n", rcvid);
        if (rcvid == -1) {      // error condition, exit
            break;
        } else if (rcvid > 0) { // test for nature of message received
            printf("Server Received Message:  %s \n", msg);
            MsgReply(rcvid, EOK, 0, 0);
        }
    }

    name_detach(attach, 0);     // remove the name from the space
    return EXIT_SUCCESS;
}

//***************************************************************************************
// Client Side of the code
//***************************************************************************************
int client() {
    char msg[30];
    int fd, count = 0;

    if ((fd = name_open("myserver", 0)) == -1) {
        return EXIT_FAILURE;
    }

    printf("Client Sending %d \n", msg);
    printf("The channel ID Client is %d\n", fd);
    while (1) {     // Do work with server connection
        sprintf(msg, "\nPlease Reply: %4x(Hex)\n", count);
        if (MsgSend(fd, &msg, sizeof(msg), NULL, 0) == -1) break;
        ++count;
        delay(500);
    }

    name_close(fd); // Close the connection
    return EXIT_SUCCESS;
}

//***********************************************************************************
// The main function - allow eash housekeeping
// - one program two processes by using "-s" or "-c"
//***********************************************************************************
int main(int argc, char **argv) {
    int ret;

    if (argc < 2) {
        printf("Usage %s -s | -c \n", argv[0]);
        ret = EXIT_FAILURE;
    } else if (strcmp(argv[1], "-c") == 0) {
        printf("Running Client ... \n");
        ret = client();
    } else if (strcmp(argv[1], "-s") == 0) {
        printf("Running Server ... \n");
        ret = server();
    } else {
        printf("Usage %s -s | -c \n", argv[0]);
        ret = EXIT_FAILURE;
    }

    exit(0);
}
 
 