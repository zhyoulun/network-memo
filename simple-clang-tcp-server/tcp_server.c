#include "unp.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>


int main(int argc, char **argv){
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if (listenfd==-1){
        printf("socket fail\n");
        exit(1);
    }

    
}