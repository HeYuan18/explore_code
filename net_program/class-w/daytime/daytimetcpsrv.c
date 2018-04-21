/*************************************************************************
	> File Name: daytimetcpsrv.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月22日 星期四 14时17分04秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<unp.h>

int main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	serverAddr, clientAddr;
    socklen_t           clientAddr_len = sizeof(clientAddr);
	char				buff[MAXLINE];
	time_t				ticks;

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
        //printf("IP = %s, PORT = %d connected\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n%s\r\n", ctime(&ticks), "Hello Future!");
        Write(connfd, buff, strlen(buff));

		Close(connfd);
	}

    return 0;
}
