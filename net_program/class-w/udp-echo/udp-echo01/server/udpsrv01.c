/*************************************************************************
	> File Name: udpsrv01.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月28日 星期六 14时37分48秒
 ************************************************************************/

#include<stdio.h>
#include<unp.h>

int main(int argc, char* argv[])
{
    void dg_echo(int, SA*, socklen_t);
    void sig_chld(int);
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);        
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(sockfd, (SA*)&servaddr, sizeof(servaddr));
    Signal(SIGCHLD, sig_chld);
    dg_echo(sockfd, (SA*)&cliaddr, sizeof(cliaddr));
}
