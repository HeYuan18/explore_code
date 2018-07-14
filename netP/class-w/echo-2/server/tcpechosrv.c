/*************************************************************************
	> File Name: tcpechosrv.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月12日 星期四 20时28分14秒
 ************************************************************************/

#include<stdio.h>
#include<unp.h>


int main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	serverAddr, clientAddr;
    socklen_t           clientAddr_len = sizeof(clientAddr);

    int i = 0, maxi, maxfd = 0, sockfd;
    int nready = 0, client[FD_SETSIZE];
    int rlen = 0;
    char buff[MAXLINE];
    fd_set rset, allset;

    void sig_chld(int);
    void upTOlow(char* const, int);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family      = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port        = htons(4399);	/* daytime server */

    int optval = 1;
    Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	Bind(listenfd, (SA *) &serverAddr, sizeof(serverAddr));

	Listen(listenfd, LISTENQ);

    Signal(SIGCHLD, sig_chld);

    maxfd = listenfd;
    maxi = -1;
    for(; i < FD_SETSIZE; ++i)
    {
        client[i] = -1;
    }
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    while(1)
    {
        rset = allset;
        nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(listenfd, &rset))
        {
            connfd = Accept(listenfd, (SA*)&clientAddr, &clientAddr_len);

            for(i = 0; i < FD_SETSIZE; ++i)
            {
                if(client[i] < 0)
                {
                    client[i] = connfd;
                    break;
                }
            }
            if(i == FD_SETSIZE)
            {
                err_quit("too many clients");
            }

            FD_SET(connfd, &allset);
            maxfd = maxfd > connfd ? maxfd : connfd;
            maxi = maxi > i ? maxi : i;

            if(--nready <= 0)
            {
                continue;
            }
        } 

        for(i = 0; i <= maxi; ++i)
        {
            if((sockfd = client[i]) < 0)
            {
                continue;
            }
            if(FD_ISSET(sockfd, &rset))
            {
                if((rlen = Readline(sockfd, buff, MAXLINE)) == 0)
                {
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else
                {
                    upTOlow(buff, rlen);
                    Write(sockfd, buff, rlen);
                }

                if(--nready <= 0)
                {
                    break;
                }
            }
        }
    }


    return 0;
}
