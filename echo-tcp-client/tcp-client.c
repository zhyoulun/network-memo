#include "unp.h"

void str_cli(FILE *fp, int connfd);

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
    {
        err_quit("usage: tcpcli <IPAddresss>");
    }

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);
    return 0;
}

void str_cli(FILE *fp, int connfd)
{
    char buf[MAXLINE];
    int maxfdp1 = max(fileno(fp), connfd) + 1;
    fd_set rset;
    int stdineof = 0;
    int n;

    FD_ZERO(&rset);
    while (1)
    {
        if (stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(connfd, &rset);
        Select(maxfdp1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(connfd, &rset))
        {
            if ((n = Read(connfd, buf, MAXLINE)) == 0) //socket is readable
            {
                if (stdineof == 1)
                    return; //normal terminated
                else
                    err_quit("str_cli: server terminated permaturely");
            }
            Writen(fileno(stdout), buf, n);
        }

        if (FD_ISSET(fileno(fp), &rset))
        {
            if ((n = Read(fileno(fp), buf, MAXLINE)) == 0) //input is readable
            {
                stdineof = 1;
                Shutdown(connfd, SHUT_WR); //send FIN
                FD_CLR(fileno(fp), &rset);
                write(stdout, "Fgets EOF\n", 10);
                continue;
            }
            Writen(connfd, buf, n);
        }
    }
}