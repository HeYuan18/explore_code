/*************************************************************************
	> File Name: cli.c
	> Author: karma1996
	> Mail: karma1996@foxmail.com
	> Created Time: 2018年06月29日 星期五 10时28分13秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

#define S_IP    "39.106.138.155"
#define S_PORT  4399
#define buf_len 1024

char buf[buf_len];

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;
typedef struct remote
{
    int             port;
    struct in_addr  ip;
}Remote;

int main(int argc, char* argv[])
{
    int sockfd;
    
    SA_IN server;
    bzero(&server, sizeof(SA_IN));
    server.sin_family = AF_INET;
    server.sin_port = htons(S_PORT);
    server.sin_addr.s_addr = inet_addr(S_IP);

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");

        return -1;
    }
    printf("......\n");

    memset(buf, 0, sizeof(buf));

    /*向服务器发送心跳包，通知服务器自己的公网IP+PORT*/
    sendto(sockfd, buf, sizeof(char), 0, (SA*)&server, sizeof(SA_IN));
    
    printf("......\n");
    while(1)
    {
        
    }

    close(sockfd);

    return 0;
}
