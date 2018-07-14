/*************************************************************************
	> File Name: daytimetcpsrv.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月22日 星期四 14时17分04秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<unp.h>

void str_echo(int connfd)
{
    int n = 0;
    char buff[MAXLINE];

    while((n = Read(connfd, buff, MAXLINE)) != 0)
    {
        Writen(connfd, buff, n);
    }
}

int main(int argc, char **argv)
{
	int					listenfd, connfd, pid;
	struct sockaddr_in	serverAddr, clientAddr;
    socklen_t           clientAddr_len = sizeof(clientAddr);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family      = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port        = htons(4399);	/* daytime server */

    int optval = 1;
    Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	Bind(listenfd, (SA *) &serverAddr, sizeof(serverAddr));

	Listen(listenfd, LISTENQ);

	for( ; ; )
    {
		connfd = Accept(listenfd, (SA *)&clientAddr, &clientAddr_len);

        if((pid = fork()) == 0)
        {
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }
		Close(connfd);
	}

    return 0;
}
