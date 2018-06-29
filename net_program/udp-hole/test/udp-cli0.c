/*************************************************************************
	> File Name: udp-cli0.c
	> Author: karma1996
	> Mail: karma1996@foxmail.com
	> Created Time: 2018年06月27日 星期三 19时11分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

#define S_IP "39.106.138.155"
//#define S_IP "127.0.0.1"
#define S_PORT 4399
#define max_buf 1024

char buf[max_buf];

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;
typedef struct session
{
    int port;
    struct in_addr ip;
}Session;

/*回射服务器*/
void echo_session(int sockfd, SA* addr, socklen_t* len)
{
    while(1)
    {
        memset(buf, 0, sizeof(buf));

        /*接收cli1发来的数据*/
        recvfrom(sockfd, buf, sizeof(buf) - 1, 0, addr, len);
        printf("len:%lu\n", strlen(buf));
        printf("rcv: %s\n", buf);
        /*向cli1发送数据*/
        sendto(sockfd, buf, strlen(buf), 0, addr, sizeof(SA_IN));

        buf[strlen(buf) - 1] = '\0';
        if(strcmp(buf, "exit") == 0)
        {
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    int sockfd;
    Session cli;

    SA_IN server, p_cli1;
    bzero(&server, sizeof(SA_IN));
    bzero(&p_cli1, sizeof(SA_IN));
    socklen_t addrlen = sizeof(SA_IN);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(S_IP);
    server.sin_port = htons(S_PORT);

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");

        return -1;
    }
    
    /*向服务器发送公网IP+PORT*/
    sendto(sockfd, buf, sizeof(char), 0, (SA*)&server, sizeof(SA_IN));
    /*接收cli1的公网IP+PORT*/
    memset(buf, 0, sizeof(buf));
    recvfrom(sockfd, buf, sizeof(Session), 0, (SA*)&server, &addrlen);
    memcpy(buf, &cli, sizeof(Session));

    printf("IP: %s\tPORT: %d\n", inet_ntoa(cli.ip), ntohs(cli.port));
    
    p_cli1.sin_addr = cli.ip;
    p_cli1.sin_port = cli.port;

    sendto(sockfd, buf, sizeof(char), 0, (SA*)&server, sizeof(SA_IN));

    echo_session(sockfd, (SA*)&p_cli1, &addrlen);

    close(sockfd);
    return 0;
}
