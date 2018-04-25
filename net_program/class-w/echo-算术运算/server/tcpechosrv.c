/*************************************************************************
	> File Name: tcpechosrv.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月12日 星期四 20时28分14秒
 ************************************************************************/

#include<stdio.h>
#include<unp.h>


int main()
{
	int					listenfd, connfd, pid;
	struct sockaddr_in	serverAddr, clientAddr;
    socklen_t           clientAddr_len = sizeof(clientAddr);
    void sig_chld(int);
    void str_echo(int);

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


	for( ; ; )
    {
		connfd = Accept(listenfd, (SA *)&clientAddr, &clientAddr_len);

        if(0 == (pid = fork()))
        {
            Close(listenfd);
            str_echo(connfd);

            exit(0);
        }
		Close(connfd);
	}

    return 0;
}
