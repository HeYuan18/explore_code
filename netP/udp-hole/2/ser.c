/*************************************************************************
	> File Name: ser.c
	> Author: karma1996
	> Mail: karma1996@foxmail.com
	> Created Time: 2018年06月29日 星期五 16时48分53秒
 ************************************************************************/

#include<error.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define S_PORT  4399
#define buf_len 1024

char buf[buf_len];

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;
typedef struct remote
{
    int port;
    struct in_addr ip;
}Remote;

int main(int argc, char* argv[])
{
    Remote cli[2];
    int sockfd;

    SA_IN server, client;
    socklen_t addrlen = sizeof(SA_IN);

    bzero(&server, sizeof(SA_IN));
    server.sin_family = AF_INET;
    server.sin_port = htons(S_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bzero(&client, sizeof(SA_IN));
    client.sin_family = AF_INET;

    if((sockfd = socket(AF_INET,SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        
        return -1;
    }
    if(bind(sockfd, (SA*)&server, sizeof(SA_IN)) == -1)
    {
        perror("bind");

        return -1;
    }
    
    while(1)
    {
        memset(cli, 0, 2 * sizeof(Remote));

        memset(buf, 0, sizeof(buf));
        /*接收cli0发送的心跳包，获取其外网IP+PORT*/
        int ret = recvfrom(sockfd, &buf, sizeof(buf) - 1, 0, (SA*)&client, &addrlen);
        if(ret <= 0)
        {
            printf("recv error\n");
            continue;
        }
        memcpy(&cli[0].ip, &client.sin_addr, sizeof(struct in_addr));
        cli[0].port = client.sin_port;

        memset(buf, 0, sizeof(buf));
        /*接收cli1发送的心跳包，获取其外网IP+PORT*/
        ret = recvfrom(sockfd, &buf, sizeof(buf) - 1, 0, (SA*)&client, &addrlen);
        if(ret <= 0)
        {
            printf("recv error\n");
            continue;
        }
        memcpy(&cli[1].ip, &client.sin_addr, sizeof(struct in_addr));
        cli[1].port = client.sin_port;

        memset(buf, 0, sizeof(buf));
        /*向cli1发送cli0的公网IP+PORT*/
        memcpy(buf, &cli[0], sizeof(Remote));
        sendto(sockfd, buf, sizeof(Remote), 0, (SA*)&client, sizeof(SA_IN));

        memset(buf, 0, sizeof(buf));
        /*向cli0发送cli1的公网IP+PORT*/
        memcpy(buf, &cli[1], sizeof(Remote));
        memcpy(&client.sin_addr, &cli[0].ip, sizeof(struct in_addr));
        client.sin_port = cli[0].port;
        sendto(sockfd, buf, sizeof(Remote), 0, (SA*)&client, sizeof(SA_IN));

        printf("cli0> IP: %s\tPORT: %d OK\n", inet_ntoa(cli[0].ip), htons(cli[0].port));
        printf("cli1> IP: %s\tPORT: %d OK\n", inet_ntoa(cli[1].ip), htons(cli[1].port));
        fflush(stdout);
    }


    return 0;
}

