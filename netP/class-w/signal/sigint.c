/*************************************************************************
	> File Name: sigint.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月02日 星期一 20时01分47秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<unp.h>

void sig_int(int signo)
{
    char *const argv[] = {"sudo", "reboot", NULL};

    execvp("reboot", argv);
}

int main()
{
    Signal(SIGINT, sig_int);

    while(1);

    return 0;
}
