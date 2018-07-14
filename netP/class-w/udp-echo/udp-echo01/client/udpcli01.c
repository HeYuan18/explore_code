/*************************************************************************
	> File Name: udpcli01.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月28日 星期六 14时49分45秒
 ************************************************************************/

#include<stdio.h>
#include<unp.h>

int main(int argc, char* argv[])
{
    void dg_cli(FILE*, int, const SA*, socklen_t);
    int sockfd;
    struct sockaddr_in servaddr;

    if(argc != 2)
    {
        err_quit("usage: udpcli <IP address>");
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));
    exit(0);
}
