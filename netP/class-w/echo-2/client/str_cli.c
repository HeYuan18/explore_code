/*************************************************************************
	> File Name: str_cli.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月12日 星期四 21时26分38秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unp.h>

void str_cli(FILE* fp, int sockfd)
{
    int maxfdp1;
    fd_set rset;
    char buff[MAXLINE];

    FD_ZERO(&rset);
    while(1)
    {
        FD_SET(0, &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(0, sockfd) + 1;

        Select(maxfdp1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(sockfd, &rset))
        {
            if(Readline(sockfd, buff, MAXLINE) == 0)
            {
                err_quit("str_cli: server terminated prematurely");
            }
            Fputs(buff, stdout);
        }
        if(FD_ISSET(0, &rset))
        {
            if(Fgets(buff, MAXLINE, fp) == NULL)
            {
                return;
            }
            Write(sockfd, buff, strlen(buff));
        }
    }
}
