/*************************************************************************
	> File Name: cli0.c
	> Author: karma1996
	> Mail: karma1996@foxmail.com
	> Created Time: 2018年06月30日 星期六 11时14分07秒
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
#define C_PORT  7373
#define buf_len 1024

char buf[buf_len];

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;
typedef struct remote
{
    int             port;
    struct in_addr  ip;
}Remote;

/*打通双向洞-----双方正常通信*/
void sendtoMsg(int sockfd, SA* addr, socklen_t* len)
{
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        printf("> ");
        fgets(buf, sizeof(buf), stdin);
        /*向cli1发送数据*/
        sendto(sockfd, buf, strlen(buf), 0, addr, sizeof(SA_IN));

        memset(buf, 0, sizeof(buf));
        /*接收cli1发来的数据*/
        recvfrom(sockfd, buf, sizeof(buf) - 1, 0, addr, len);
        printf("rcv: %s\n", buf);
        fflush(stdout);

        buf[strlen(buf) - 1] = '\0';
        if(strcmp(buf, "exit") == 0)
        {
            printf("sys: exit......\n");
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    int sockfd;
    Remote r_cli1;
    
    SA_IN server, cli0, p_cli1;
    socklen_t addrlen = sizeof(SA_IN);

    bzero(&server, sizeof(SA_IN));
    server.sin_family = AF_INET;
    server.sin_port = htons(S_PORT);
    server.sin_addr.s_addr = inet_addr(S_IP);

    bzero(&cli0, sizeof(SA_IN));
    cli0.sin_family = AF_INET;
    cli0.sin_port = htons(C_PORT);
    cli0.sin_addr.s_addr = INADDR_ANY;

    bzero(&p_cli1, sizeof(SA_IN));
    p_cli1.sin_family = AF_INET;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");

        return -1;
    }
    if(bind(sockfd, (SA*)&cli0, sizeof(SA_IN)) == -1)
    {
        perror("bind");

        return -1;
    }

    memset(buf, 0, sizeof(buf));
    /*向服务器发送心跳包，通知服务器自己的公网IP+PORT*/
    sendto(sockfd, buf, sizeof(char), 0, (SA*)&server, sizeof(SA_IN));

    memset(buf, 0, sizeof(buf));
    /*从服务器获取cli1的公网IP+PORT*/
    int ret = recvfrom(sockfd, &buf, sizeof(buf) - 1, 0, (SA*)&server, &addrlen);
    if(ret <= 0)
    {
        printf("recv error\n");
        
        return -1;
    }
    memcpy(&r_cli1, buf, sizeof(Remote));
    printf("IP: %s\tPORT: %d OK\n", inet_ntoa(r_cli1.ip), htons(r_cli1.port));
    fflush(stdout);

    /*接收cli1的打洞请求-----网关屏蔽陌生信息----为了安全*/
    /*
    ret = recvfrom(sockfd, buf, sizeof(buf) - 1, 0, (SA*)&p_cli1, &addrlen);
    if(ret <= 0)
    {
        printf("recv abnormal\n");
    }
    */

    memcpy(&p_cli1.sin_addr, &r_cli1.ip, sizeof(struct in_addr));
    p_cli1.sin_port = r_cli1.port;
    /*打通cli1到cli0的单向洞-----允许cli1向cli0发送数据*/
    sendtoMsg(sockfd, (SA*)&p_cli1, &addrlen);

    close(sockfd);

    return 0;
}
