#include "unp.h"

void str_cli(int connfd);

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
    str_cli(sockfd);
    return 0;
}

void str_cli(int connfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];
    while (1)
    {
        if (Fgets(sendline, MAXLINE, stdin) == NULL)
        {
            write(stdout, "Fgets EOF\n", 10);
            break;
        }
        Writen(connfd, sendline, strlen(sendline));
        if (Readline(connfd, recvline, MAXLINE) == 0)
        {
            err_quit("str_cli: server terminated permaturely");
        }
        Fputs(recvline, stdout);
    }
}