/*************************************************************************
	> File Name: ser.c
	> Author: karma1996
	> Mail: karma1996@foxmail.com
	> Created Time: 2018年06月29日 星期五 10时28分06秒
 ************************************************************************/

#include<error.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

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
    Remote cli;
    int sockfd;

    SA_IN server, client;
    socklen_t addrlen = sizeof(SA_IN);
    bzero(&client, sizeof(SA_IN));
    client.sin_family = AF_INET;
    bzero(&server, sizeof(SA_IN));
    server.sin_family = AF_INET;
    server.sin_port = htons(4399);
    server.sin_addr.s_addr = INADDR_ANY;

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
        memset(buf, 0, sizeof(buf));
        memset(&cli, 0, sizeof(Remote));

        /*接收客户端发送的心跳包，检验其外网IP+PORT*/
        int ret = recvfrom(sockfd, &buf, sizeof(buf) - 1, 0, (SA*)&client, &addrlen);
        if(ret <= 0)
        {
            printf("recv error\n");
            continue;
        }
        memcpy(&cli.ip, &client.sin_addr, sizeof(struct in_addr));
        cli.port = client.sin_port;

        printf("IP: %s\tPORT: %d\n", inet_ntoa(cli.ip), htons(cli.port));
        fflush(stdout);
    }


    return 0;
}
