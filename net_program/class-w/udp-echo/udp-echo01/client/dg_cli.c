/*************************************************************************
	> File Name: dg_cli.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月28日 星期六 14时57分31秒
 ************************************************************************/

#include<stdio.h>
#include<unp.h>

void dg_cli(FILE* fp, int sockfd, const SA* pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    while(Fgets(sendline, MAXLINE, fp) != NULL)
    {
        sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

        recvline[n] = 0;
        Fputs(recvline, stdout);
    }
}
