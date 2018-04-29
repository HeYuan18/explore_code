/*************************************************************************
	> File Name: sigchldwaitpid.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月12日 星期四 20时28分58秒
 ************************************************************************/

#include<unp.h>

void sig_chld(int no)
{
    pid_t pid;
    int stat;

    while(0 < (pid = waitpid(-1, &stat, WNOHANG)))
    {
        //printf("child %d terminated\n", pid);
    }
}
    
