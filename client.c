#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(int argc, char **argv) {
    if (argc == 1) {
        puts("ERROR: Must inlcude option -c for just client or -s for client and server");
        }
    else if (argc == 2) {
        if(strcmp(argv[1], "-c")==0) {
            puts("starting just the client");
        }
        else if (strcmp(argv[1], "-s")==0) {
            puts("starting client and server");
        }
        else puts("invalid option");
    }
    else {
        puts("too many arguments");
    }
    return 0;
}
        
