#include "unp.h"

int main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in in_cliaddr, servaddr;

    int maxi, maxfd;
    int n;
    int i;
    int client[FD_SETSIZE];
    int nready;
    fd_set rset, allset;

    char buf[MAXLINE];

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    maxfd = listenfd;
    maxi = -1;
    for (i = 0; i < FD_SETSIZE; i++)
    {
        client[i] = -1;
    }
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    for (;;)
    {
        rset = allset;
        nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (FD_ISSET(listenfd, &rset))
        {
            clilen = sizeof(in_cliaddr);
            connfd = Accept(listenfd, (SA *)&in_cliaddr, &clilen);
            for (i = 0; i < FD_SETSIZE; i++)
            {
                if (client[i] == -1)
                {
                    client[i] = connfd;
                    break;
                }
            }
            if (i == FD_SETSIZE)
            {
                err_quit("too many clients");
            }
            FD_SET(connfd, &allset);
            if (connfd > maxfd)
            {
                maxfd = connfd;
            }
            if (i > maxi)
            {
                maxi = i;
            }
            nready--;
            if (nready <= 0)
            {
                continue;
            }
        }

        for (i = 0; i < FD_SETSIZE; i++)
        {
            if ((connfd = client[i]) < 0)
            {
                continue;
            }
            if (FD_ISSET(connfd, &rset))
            {
                if ((n = Read(connfd, buf, MAXLINE)) == 0)
                {
                    Close(connfd);
                    FD_CLR(connfd, &allset);
                    client[i] = -1;
                }
                else
                {
                    Writen(connfd, buf, n);
                }
                nready--;
                if (nready <= 0)
                {
                    break;
                }
            }
        }
    }
}