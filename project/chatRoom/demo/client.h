/*************************************************************************
	> File Name: client.h
	> Author: 
	> Mail: 
	> Created Time: 2017年12月03日 星期日 22时24分10秒
 ************************************************************************/

#ifndef _CLIENT_H
#define _CLIENT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netdb.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"stdfx.h"

memberList member;
char member_buf[__member_len__];
message msg;
char msg_buf[__msg_len__];
run Run;

char recordMsg[max_msg_size + __name_len__ + 2];
char name[__name_len__];
char dir_msg[] = ".RMSG";
char path[35];
char colon[] = ": ";

void initMember()
{
    member.flag = 0;
    member.count = 0;
    member.login = -1;
    member.logout = -1;
    for(int i = 0; i < __FD_NUM__; ++i)
    {
        member.client[i].fd = -1;
        memset(member.client[i].name, 0, sizeof(member.client[i].name));
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

void mkdir_msgRecord()
{
    if(access(dir_msg, F_OK) != 0)
    {
        if(mkdir(dir_msg, S_IRWXU) == -1)
        {
            perror("mkdir");
        }
    }
}

void print_memberList()
{
    system("clear");
    printf("\n\n==============聊天室成员==============\n\n");
    int count = 0;
    for(int i = 0; i < __FD_NUM__; ++i)
    {
        if(member.client[i].fd == -1)
        {
            continue;
        }
        printf("\t%d -----> %s\n", ++count, member.client[i].name);
    }
    printf("\n\t\t\t聊天室人数: %d\n", member.count);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("input \"cls\" ,       清屏\n");
    printf("input \"Quit\",       退出聊天室\n");
    printf("input \"print_msg\" , 查看消息记录\n");
    printf("=======================================\n");
    fflush(stdout);
}

void print_message()
{
    FILE *fp = NULL;
    char *text = NULL;

    printf("\n\n==============消息列表==============\n\n");
    if((fp = fopen(path, "r")) == NULL)
    {
        //perror("fopen");
        printf("消息记录列表空\n");
    }
    else
    {
        fseek(fp, 0, SEEK_END);
        long fsize = ftell(fp);
        rewind(fp);

        text = (char*)malloc(fsize + 1);
        memset(text, 0, sizeof(text));
        fread(text, sizeof(char), fsize, fp);
        fclose(fp);

        text[fsize] = '\0';
        printf("%s", text);

        free(text);
        text = NULL;
    }
    printf("\n=======================================\n");
    fflush(stdout);
}

int handle_connect(int sockfd)
{
    memset(msg_buf, 0, __msg_len__);

    recv(sockfd, msg_buf, __msg_len__, 0);
    memcpy(&Run, msg_buf, __run_len__);
    if(Run.status == normal)
    {
        printf("====================服务器链接成功====================\n");
        fflush(stdout);

        memset(name, 0, __name_len__);
        printf("Please input name: ");
        scanf("%s", name);
        char c;
        while((c = getchar()) != '\n' && c != EOF);

        memset(msg_buf, 0, __msg_len__);
        memset(member_buf, 0, __member_len__);

        snprintf(path, sizeof(path), "%s%s%s%s", dir_msg, "/", name, __TIME__);
        strcpy(msg.buffer, name);
        memcpy(msg_buf, &msg, __msg_len__);
        send(sockfd, msg_buf, __msg_len__, 0);
        
        recv(sockfd, member_buf, __member_len__, 0);
        memcpy(&member, member_buf, __member_len__);
        print_memberList();
        printf("%s,欢迎加入聊天室\n", member.client[member.login].name);
        printf("---------------------\n");
        fflush(stdout);

        return normal;
    }
    if(Run.status == client_max_count)
    {
        printf("聊天室人数达到上限，请稍后重连......\n");
        return client_max_count;
    }
}

int handle_input(int sockfd)
{
    memset(msg_buf, 0, __msg_len__);

    char enter[] = "\n";
    char quit[] = "Quit\n";
    char cls[] = "cls\n";
    char print_msg[] = "print_msg\n";
    char print_member[] = "print_member\n";

    if(strcmp(msg.buffer, enter) == 0)
    {
        return 0;
    }
    if(strcmp(msg.buffer, quit) == 0)
    {
        msg_buf[0] = 'x';
        msg_buf[1] = '\0';
        send(sockfd, msg_buf, strlen(msg_buf), 0);

        return 1;
    }
    if(strcmp(msg.buffer, cls) == 0)
    {
        system("clear");
        print_memberList();
        return 0;
    }
    if(strcmp(msg.buffer, print_msg) == 0)
    {
        print_message();
        return 0;
    }
    if(strcmp(msg.buffer, print_member)  == 0)
    {
        print_memberList();
        return 0;
    }

    memset(recordMsg, 0, sizeof(recordMsg));
    memcpy(msg_buf, &msg, sizeof(msg.buffer));
    send(sockfd, msg_buf, __msg_len__, 0);

    snprintf(recordMsg, sizeof(recordMsg), "%s%s%s", name, colon, msg.buffer);
    FILE *fp = NULL;
    if((fp = fopen(path, "at+")) == NULL)
    {
        perror("fopen");
    }
    else
    {
        fwrite(recordMsg, strlen(recordMsg), 1, fp);
        fclose(fp);
    }

    return 0;
}

void handle_output()
{
    memset(msg.buffer, 0, sizeof(msg.buffer));

    int member_or_msg = -1;
    memcpy(&member_or_msg, msg_buf, sizeof(int));
    if(member_or_msg == 0)  //更新成员列表
    {
        initMember();
        memcpy(&member, msg_buf, __member_len__);
        if(member.login != -1)    //新成员登录
        {
            system("clear");
            printf("\n\n================WeChat================\n\n");
            printf("%s, 加入聊天室\n\n", member.client[member.login].name);
            printf("\t\t\t聊天室人数: %d\n", member.count);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("input \"cls\" ,         清屏\n");
            printf("input \"Quit\",         退出聊天室\n");
            printf("input \"print_msg\",    查看消息记录\n");
            printf("input \"print_member\", 更新成员列表\n");
            printf("======================================\n");
        }
        if(member.logout != -1)   //成员下线
        {
            system("clear");
            printf("\n\n================WeChat================\n\n");
            printf("%s, 退出聊天室\n\n", member.client[member.logout].name);
            printf("\t\t\t聊天室人数: %d\n", member.count);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("input \"cls\" ,         清屏\n");
            printf("input \"Quit\",         退出聊天室\n");
            printf("input \"print_msg\",    查看消息记录\n");
            printf("input \"print_member\", 更新成员列表\n");
            printf("======================================\n");
        }
    }
    if(member_or_msg == 1)  //消息
    {
        memset(msg.buffer, 0, sizeof(msg.buffer));
        memset(recordMsg, 0, sizeof(recordMsg));

        memcpy(&msg, msg_buf, __msg_len__);
        snprintf(recordMsg, sizeof(recordMsg), "%s%s%s", member.client[msg.user].name, colon, msg.buffer);
    
        FILE *fp = NULL;
        if((fp = fopen(path, "at+")) == NULL)
        {
            perror("fopen");
        }
        else
        {
            fwrite(recordMsg, strlen(recordMsg), 1, fp);
            fclose(fp);
        }

        printf("\n\n@------------------------------------@\n");
        printf("@msg from  %s", recordMsg);
        printf("@------------------------------------@\n\n");
    }
    fflush(stdout);
}

#endif
