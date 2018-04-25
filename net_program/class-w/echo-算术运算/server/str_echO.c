/*************************************************************************
	> File Name: str_echo.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月12日 星期四 20时28分30秒
 ************************************************************************/

#include<ctype.h>
#include<string.h>
#include<unp.h>

typedef struct ope
{
    long a;
    char ope;
    long b;
    long result;
}Ope;

void str_echo(int connfd)
{
    int rlen = 0;
    Ope O;
    char buff[MAXLINE];

    while(1)
    {
        if((rlen = Readline(connfd, buff, MAXLINE)) == 0)
        {
            return;
        }
        if(sscanf(buff, "%ld%ld", &O.a, &O.b) == 2)
        {
            O.result = O.a + O.b;
            memcpy(buff, &O, sizeof(Ope));
        }
        else
        {
            snprintf(buff, sizeof(buff), "input error\n");
        }
        rlen = sizeof(Ope);

        Write(connfd, buff, rlen);
    }
}

