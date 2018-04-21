/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: 2017年12月03日 星期日 18时17分47秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"stdfx.h"

#define backlog __FD_NUM__

struct sockaddr_in clientaddr;
socklen_t clientaddr_len = sizeof(clientaddr);

memberList member;
char member_buf[__member_len__];
message msg;
char msg_buf[__msg_len__];
run Run;

void initMember()
{
    member.flag = 0;
    member.count = 0;
    member.login = -1;
    member.logout = -1;
    for(int i = 0; i < __FD_NUM__; ++i)
    {
        member.client[i].fd = -1;
        memset(member.client[i].name, 0, sizeof(__name_len__));
    }
}

void initMsg()
{
    msg.flag = 1;
    msg.user = -1;
    memset(msg.buffer, 0, sizeof(msg.buffer));
}
 void initRun()
{
    Run.flag = 2;
    Run.status = normal;
}

void send_cast(int sockfd, char msg[], int msg_len, int broadcast, int unicast)  //可广播可单播
{
    if(unicast == 1)
    {
        send(sockfd, msg, msg_len, 0);
    }
    if(broadcast == 1)
    {
        for(int i = 0; i < __FD_NUM__; ++i)
        {
            if(member.client[i].fd == -1)
            {
                continue;
            }
            if(member.client[i].fd != sockfd)
            {
                send(member.client[i].fd, msg, msg_len, 0);
            }
        }
    }
}

void set_memberList(int connfd)
{
    memset(msg_buf, 0, __msg_len__);
    memset(member_buf, 0, __member_len__);

    int i = 0;
    for(; i < __FD_NUM__; ++i)
    {
        if(member.client[i].fd == -1)
        {
            member.login = i;
            member.client[i].fd = connfd;
            member.count += 1;
            break;
        }
    }
    recv(connfd, msg_buf, __msg_len__, 0);
    memcpy(&msg, msg_buf, __msg_len__);
    strcpy(member.client[i].name, msg.buffer);

    printf("\nIP = %s, PORT = %d\t", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
    printf("\t在线人数：%d\n", member.count);
    printf("%s,您好欢迎进入聊天室。%s %s \n\n", member.client[i].name, __DATE__,__TIME__);

    memcpy(member_buf, &member, __member_len__);
    send_cast(member.client[i].fd, member_buf, __member_len__, 1, 1);

    member.login = -1;
}

void clr_memberList(int i)
{
    memset(member_buf, 0, __member_len__);

    member.logout = i;
    member.count -= 1;
    member.client[i].fd = -1;
    printf("\n%s: Quit.\t%s %s\t", member.client[i].name, __DATE__, __TIME__);
    printf("在线人数：%d\n\n", member.count);
    memcpy(member_buf, &member, __member_len__);
    send_cast(member.client[i].fd, member_buf, __member_len__, 1, 0); 
    member.logout = -1;
}

#endif
