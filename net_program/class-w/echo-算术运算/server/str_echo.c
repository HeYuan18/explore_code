/*************************************************************************
	> File Name: str_echo.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月12日 星期四 20时28分30秒
 ************************************************************************/

#include<ctype.h>
#include<unp.h>

void str_echo(int connfd)
{
    int rlen = 0;
    long a = 0, b = 0;
    char buff[MAXLINE];

    while(1)
    {
        if((rlen = Readline(connfd, buff, MAXLINE)) == 0)
        {
            return;
        }
        if(sscanf(buff, "%ld%ld", &a, &b) == 2)
        {
            snprintf(buff, sizeof(buff), "%ld\n", a + b);
        }
        else
        {
            snprintf(buff, sizeof(buff), "input error\n");
        }
        rlen = strlen(buff);

        Write(connfd, buff, rlen);
    }
}

