#include "unp.h"

void doit(int connfd);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    int len;
    struct sockaddr_in servaddr, cliaddr;
    char buff[MAXLINE];
    size_t pid;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);

    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    for (;;)
    {
        len = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA *)&cliaddr, &len);
        printf("connection from %s:%d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)), ntohs(cliaddr.sin_port));

        if ((pid = Fork()) == 0)
        { //子进程
            Close(listenfd);
            doit(connfd);
            Close(connfd);
            exit(0);
        }

        Close(connfd);
    }

    return 0;
}

void doit(int connfd)
{
    time_t ticks;
    char buff[MAXLINE];

    ticks = time(NULL);
    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    Write(connfd, buff, strlen(buff));
}