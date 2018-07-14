/*************************************************************************
	> File Name: tcpechocli.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月12日 星期四 21时25分53秒
 ************************************************************************/

#include<stdio.h>
#include<unp.h>

int main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;
    void str_cli(FILE*, int);

	if(argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(SERV_PORT);	/* daytime server */

    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);

    exit(0);
}
