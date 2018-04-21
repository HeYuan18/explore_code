/*************************************************************************
	> File Name: stdfx.h
	> Author: 
	> Mail: 
	> Created Time: 2017年12月03日 星期日 15时46分50秒
 ************************************************************************/

#ifndef _STDFX_H
#define _STDFX_H

#define port 4000

#define __name_len__ 16
typedef struct Client
{
    int fd;
    char name[__name_len__];
}clientInfo;

#define __FD_NUM__ 128      //最大连接人数127 
typedef struct MemberList
{
    int flag;
    int count;
    int login;
    int logout;
    clientInfo client[__FD_NUM__];
}memberList;
#define __member_len__ sizeof(memberList)

#define max_msg_size 4088   //必须大于2576
typedef struct Message
{
    int flag;
    int user;
    char buffer[max_msg_size];
}message;
#define __msg_len__ sizeof(message)

#define normal 0
#define client_max_count 1
typedef struct MachineRun
{
    int flag;
    int status;
}run;
#define __run_len__ sizeof(run)
#endif
