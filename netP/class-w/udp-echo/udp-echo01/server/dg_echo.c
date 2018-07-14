/*************************************************************************
	> File Name: dg_echo.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月28日 星期六 14时45分04秒
 ************************************************************************/

#include<stdio.h>
#include<unp.h>

void dg_echo(int sockfd, SA* pcliaddr, socklen_t clien)
{
    int n;
    socklen_t len;
    char mesg[MAXLINE];
    for(; ;)
    {
        len = clien;
        n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

        Sendto(sockfd, mesg, n, 0, pcliaddr, len);
    }
}
