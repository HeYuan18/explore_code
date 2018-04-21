/*************************************************************************
	> File Name: str_echo.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月12日 星期四 20时28分30秒
 ************************************************************************/

#include<ctype.h>
#include<unp.h>

void upTOlow(char* const str, int len)
{
    int i = 0;
    for(; i < len; ++i)
    {
        if('a' <= str[i] && str[i] <= 'z')
        {
            str[i] = toupper(str[i]);
        }
        else if('A' <= str[i] && str[i] <= 'Z')
        {
            str[i] = tolower(str[i]);
        }
        else
        {
            continue;
        }
    }
}

void str_echo(int connfd)
{
    int rlen = 0;
    char buff[MAXLINE];

    while(1)
    {
        if((rlen = Readline(connfd, buff, MAXLINE)) == 0)
        {
            return;
        }
        upTOlow(buff, rlen);

        Write(connfd, buff, rlen);
    }
}

